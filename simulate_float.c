/*
 * Version: 0.9.1
 * Author: Han, He <he.han@intel.com>
 * Date: Nov 21st, 2013
 * Update: Nov 27th, 2013 : Add cubic root function
 */
#include "simulate_float.h"
#include "int_roots.h"

#define SYMBOL_BIT          (0x01 << 31)
#define EXPONENT_BITS       (0xFF << 23)
#define COEFFICIENT_BITS    (0x7FFFFF)
#define COEFFICIENT_MAX     (0xFFFFFF)
#define COEFFICIENT_PER_MAX (0x1FFFFFF)
#define COEFFICIENT_MIN     (0x800000)
#define INTEGER_BIT         (1 << 23)

simulate_float int_to_sfloat(int num)
{
        simulate_float symbol = 0, sfloat;
        signed char exponent = 0;

        if (num == 0) {
                return 0;
        } else if (num < 0) {
                symbol = SYMBOL_BIT;
                sfloat = -num;
        } else {
                sfloat = num;
        }

        while (sfloat > COEFFICIENT_PER_MAX) {
                sfloat >>= 1;
                exponent++;
        }

        if (exponent || sfloat > COEFFICIENT_MAX) {
                if (sfloat & 1)
                        sfloat += 1;
                while (sfloat > COEFFICIENT_MAX) {
                        sfloat >>= 1;
                        exponent++;
                }
        }

        if (exponent == 0) {
                while (sfloat < COEFFICIENT_MIN) {
                        sfloat <<= 1;
                        exponent--;
                }
        }
        sfloat &= ~INTEGER_BIT;
        exponent = ((exponent + 23) ^ (1 << 7)) - 1;

        return symbol | sfloat |  (*(unsigned char *)&exponent) << 23;
}

enum sfloat_error_t sfloat_to_int(simulate_float sfloat, int *num)
{
        simulate_float symbol = 0;
        signed char exponent = 0;

        if ((sfloat ^ (SYMBOL_BIT)) == 0) {
                *num = 0;
                return SFLOAT_ERR_SUCCESS;
        }

        symbol = sfloat & SYMBOL_BIT;
        exponent = (sfloat & EXPONENT_BITS) >> 23;

        exponent = (exponent ^ (1 << 7)) + 1;

        if (exponent > 30) {
                return SFLOAT_ERR_INTEGER_OVERFLOW;
        } else if (exponent < -1) {
                *num = 0;
                return SFLOAT_ERR_SUCCESS;
        } else if (exponent == -1) {
                *num = 1;
                if ((int)symbol)
                        *num = -*num;
                return SFLOAT_ERR_SUCCESS;
        }

        *num = sfloat & ~(SYMBOL_BIT | EXPONENT_BITS);
        *num |= (1 << 23);

        if (exponent >= 23)
                *num <<= (exponent - 23);
        else {
                *num >>= (22 - exponent);
                if (*num & 1)
                        *num += 1;
                *num >>= 1;
        }
        if ((int)symbol)
                *num = -*num;

        return SFLOAT_ERR_SUCCESS;
}

/* add, minus, multiply and divide:
 * No overflow/infinity/NaN check for they are very seldom
 * in using, need to enhance in later version.
 */
simulate_float sfloat_add(simulate_float a, simulate_float b)
{
        signed char exponent_a, exponent_b, exponent;
        simulate_float symbol_a, symbol_b, symbol, sfloat;
        signed int snum = 0;
        short s;
        char add;

        if ((a & ~SYMBOL_BIT) == 0)
                return b;
        if ((b & ~SYMBOL_BIT) == 0)
                return a;

        /* Need to deal with overflow/infinity */
        exponent_a = (a & EXPONENT_BITS) >> 23;
        exponent_b = (b & EXPONENT_BITS) >> 23;

        /* return if a or b is infinity or NaN */
        if (exponent_a == 0xFF)
                return a;
        if (exponent_b == 0xFF)
                return b;

        exponent_a = (exponent_a ^ (1 << 7)) + 1;
        exponent_b = (exponent_b ^ (1 << 7)) + 1;

        if (exponent_a - exponent_b > 23)
                return a;

        if (exponent_b - exponent_a > 23)
                return b;

        symbol_a = a & SYMBOL_BIT;
        symbol_b = b & SYMBOL_BIT;

        a = (a & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;
        b = (b & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;

        /* base number shift left six bits to keep the precision */
        a <<= 6;
        b <<= 6;

        if ((int)(symbol_a ^ symbol_b)) // minus
                add = 0;
        else //add
                add = 1;

        if (exponent_a == exponent_b) {
                if ((int)symbol_a)
                        snum -= a;
                else
                        snum += a;
                if ((int)symbol_b)
                        snum -= b;
                else
                        snum += b;
                if (snum < 0) {
                        sfloat = -snum;
                        symbol = SYMBOL_BIT;
                } else {
                        sfloat = snum;
                        symbol = 0;
                }
                s = exponent_a;
        } else if (exponent_a > exponent_b) {
                s = exponent_a;
                symbol = symbol_a;
                b = b >> (exponent_a - exponent_b);
                if (add)
                        sfloat = a + b;
                else
                        sfloat = a - b;
        } else {
                s = exponent_b;
                symbol = symbol_b;
                a = a >> (exponent_b - exponent_a);
                if (add)
                        sfloat = b + a;
                else
                        sfloat = b - a;
        }

        if (sfloat == 0)
                return 0;

        /* exponent minus one as we shift left the base number before */
        s -= 6;

        if (sfloat > COEFFICIENT_MAX) {
                while (sfloat > COEFFICIENT_PER_MAX) {
                        sfloat >>= 1;
                        s++;
                }
                if (sfloat & 1)
                        sfloat += 1;
                while (sfloat > COEFFICIENT_MAX) {
                        sfloat >>= 1;
                        s++;
                }
        } else {
                while (sfloat < COEFFICIENT_MIN) {
                        sfloat <<= 1;
                        s--;
                }
        }

        sfloat &= ~INTEGER_BIT;
        if (s > 127) {
                sfloat = 0;
                exponent = 0xFF;
        } else if (s < -127) {
                sfloat = 0;
                exponent = 0;
        } else {
                exponent = s;
                exponent = (exponent ^ (1 << 7)) - 1;
        }

        return symbol | sfloat | (*(unsigned char *)&exponent) << 23;
}

simulate_float sfloat_minus(simulate_float a, simulate_float b)
{
        return sfloat_add(a, b ^ SYMBOL_BIT);
}

simulate_float sfloat_multiply(simulate_float a, simulate_float b)
{
        signed char exponent_a, exponent_b, exponent;
        simulate_float symbol_a, symbol_b, symbol, sfloat;
        short s;
        /* using 64-bit to increase accuracy */
        unsigned long long ll;

        if ((a & ~SYMBOL_BIT) == 0 || (b & ~SYMBOL_BIT) == 0) {
                symbol = (a & SYMBOL_BIT) ^ (b & SYMBOL_BIT);
                return symbol | 0;
        }

        /* Need to deal with overflow/infinity */
        exponent_a = (a & EXPONENT_BITS) >> 23;
        exponent_b = (b & EXPONENT_BITS) >> 23;

        /* return if a or b is infinity or NaN */
        if (exponent_a == 0xFF)
                return a;
        if (exponent_b == 0xFF)
                return b;

        exponent_a = (exponent_a ^ (1 << 7)) + 1;
        exponent_b = (exponent_b ^ (1 << 7)) + 1;

        symbol_a = a & SYMBOL_BIT;
        symbol_b = b & SYMBOL_BIT;

        a = (a & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;
        b = (b & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;

        ll = ((unsigned long long)a << 8) * ((unsigned long long)b << 8);
        s = exponent_a + exponent_b;
        if (ll & ((unsigned long long)1 << 63)) {
                s++;
                sfloat = ll >> 39;
        } else
                sfloat = ll >> 38;
        if (sfloat & 1)
                sfloat += 1;
        sfloat >>= 1;
        if (sfloat > COEFFICIENT_MAX) {
                sfloat >>= 1;
                s++;
        }
        sfloat &= ~INTEGER_BIT;

        if (s > 127) {
                sfloat = 0;
                exponent = 0xFF;
        } else if (s < -127) {
                sfloat = 0;
                exponent = 0;
        } else {
                exponent = s;
                exponent = (exponent ^ (1 << 7)) - 1;
        }
        symbol = symbol_a ^ symbol_b;

        return symbol | sfloat | (*(unsigned char *)&exponent) << 23;
}

simulate_float sfloat_divide(simulate_float a, simulate_float b)
{
        signed char exponent_a, exponent_b, exponent;
        simulate_float symbol_a, symbol_b, symbol, sfloat;
        short s;

        symbol = (a & SYMBOL_BIT) ^ (b & SYMBOL_BIT);
        if ((a & ~SYMBOL_BIT) == 0 && !((b & ~SYMBOL_BIT) == 0)) {
                return symbol | 0;
        }
        if ((b & ~SYMBOL_BIT) == 0 && !((a & ~SYMBOL_BIT) == 0)) {
                return symbol | SFLOAT_POSITIVE_INFINITY;
        }
        if ((b & ~SYMBOL_BIT) == 0 && (a & ~SYMBOL_BIT) == 0) {
                return symbol | SFLOAT_POSITIVE_NAN;
        }
        /* Need to deal with overflow/infinity */
        exponent_a = (a & EXPONENT_BITS) >> 23;
        exponent_b = (b & EXPONENT_BITS) >> 23;

        /* return if a or b is infinity or NaN */
        if (exponent_a == 0xFF)
                return a;
        if (exponent_b == 0xFF)
                return b;

        exponent_a = (exponent_a ^ (1 << 7)) + 1;
        exponent_b = (exponent_b ^ (1 << 7)) + 1;

        symbol_a = a & SYMBOL_BIT;
        symbol_b = b & SYMBOL_BIT;

        a = (a & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;
        b = (b & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;

        s = exponent_a - exponent_b;
        sfloat = (a << 8) / (b >> 8);
        if (sfloat & (1 << 16))
                sfloat <<= 7;
        else {
                sfloat <<= 8;
                s--;
        }
        if ((a << 8) % (b >> 8) > (b >> 1))
                sfloat += 1;
        if (sfloat > COEFFICIENT_MAX) {
                sfloat >>= 1;
                s++;
        }
        sfloat &= ~INTEGER_BIT;

        if (s > 127) {
                sfloat = 0;
                exponent = 0xFF;
        } else if (s < -127) {
                sfloat = 0;
                exponent = 0;
        } else {
                exponent = s;
                exponent = (exponent ^ (1 << 7)) - 1;
        }
        symbol = symbol_a ^ symbol_b;

        return symbol | sfloat | (*(unsigned char *)&exponent) << 23;
}

enum sfloat_compare_t sfloat_compare(simulate_float a, simulate_float b)
{
        simulate_float symbol_a, symbol_b;
        signed char exponent_a, exponent_b;

        if (a == b)
                return SFLOAT_EQUAL_TO;

        symbol_a = a & SYMBOL_BIT;
        symbol_b = b & SYMBOL_BIT;

        /* Not deal with NaN */
        if ((a & ~SYMBOL_BIT) == 0) {
                if ((b & ~SYMBOL_BIT) == 0) {
                        return SFLOAT_EQUAL_TO;
                }

                if ((int)symbol_b)
                        return SFLOAT_GREATER_THAN;
                else
                        return SFLOAT_LESS_THAN;
        }

        if ((b & ~SYMBOL_BIT) == 0) {
                if ((int)symbol_a)
                        return SFLOAT_LESS_THAN;
                else
                        return SFLOAT_GREATER_THAN;
        }

        if ((int)symbol_a && !(int)symbol_b)
                return SFLOAT_LESS_THAN;
        if ((int)symbol_b && !(int)symbol_a)
                return SFLOAT_GREATER_THAN;

        /* Need to deal with overflow/infinity */
        exponent_a = (a & EXPONENT_BITS) >> 23;
        exponent_b = (b & EXPONENT_BITS) >> 23;

        exponent_a = (exponent_a ^ (1 << 7)) + 1;
        exponent_b = (exponent_b ^ (1 << 7)) + 1;

        if (exponent_a < exponent_b) {
                /* Negative */
                if ((int)symbol_a)
                        return SFLOAT_GREATER_THAN;
                else
                        return SFLOAT_LESS_THAN;
        }

        if (exponent_a > exponent_b) {
                /* Negative */
                if ((int)symbol_a)
                        return SFLOAT_LESS_THAN;
                else
                        return SFLOAT_GREATER_THAN;
        }

        a = (a & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;
        b = (b & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;

        if (a < b) {
                /* Negative */
                if ((int)symbol_a)
                        return SFLOAT_GREATER_THAN;
                else
                        return SFLOAT_LESS_THAN;
        }

        if (a > b) {
                /* Negative */
                if ((int)symbol_a)
                        return SFLOAT_LESS_THAN;
                else
                        return SFLOAT_GREATER_THAN;
        }

        /* it should not happen */
        return SFLOAT_COMPARE_UNKNOWN;
}

simulate_float sfloat_sqrt(simulate_float sfloat)
{
        signed char exponent, remainder;

        exponent = (sfloat & EXPONENT_BITS) >> 23;
        exponent = (exponent ^ (1 << 7)) + 1;

        remainder = exponent % 2;
        exponent /= 2;

        /* ignore symbol */
        sfloat = (sfloat & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;

        if (remainder == 0) {
                sfloat <<= 7;
        } else if (remainder < 0) {
                sfloat <<= 8;
                exponent -= 1;
        } else {
                sfloat <<= 8;
        }

        sfloat = int_sqrt(sfloat);

        /* max is 65536(17 bits) and min is 46341(16 bits) */
        if (sfloat & (1 << 16)) {
                sfloat <<= 7;
                /* carried by int_sqrt */
                exponent += 1;
        } else {
                sfloat <<= 8;
        }

        sfloat &= ~INTEGER_BIT;
        exponent = (exponent ^ (1 << 7)) - 1;

        return sfloat | (*(unsigned char *)&exponent) << 23;
}

simulate_float sfloat_cbrt(simulate_float sfloat)
{
        signed char exponent, remainder;
        simulate_float symbol;
        uint32_t root;
        uint64_t cubic = 0;

        exponent = (sfloat & EXPONENT_BITS) >> 23;
        exponent = (exponent ^ (1 << 7)) + 1;

        remainder = exponent % 3;
        exponent /= 3;

        symbol = sfloat & SYMBOL_BIT;
        /* ignore symbol */
        sfloat = (sfloat & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;

        switch (remainder) {
        case 0:
                cubic = (uint64_t)sfloat << 40;
                break;
        case -2:
                exponent--;
        case 1:
                cubic = (uint64_t)sfloat << 38;
                break;
        case -1:
                exponent--;
        case 2:
                cubic = (uint64_t)sfloat << 39;
                break;
        default:
                break;
        }

        root = int_cbrt(cubic);

        if (root & (1 << 21)) {
                sfloat = root << 2;
        } else {
                sfloat = root << 3;
        }

        sfloat &= ~INTEGER_BIT;
        exponent = (exponent ^ (1 << 7)) - 1;

        return sfloat | (*(unsigned char *)&exponent) << 23 | symbol;
}

simulate_float sfloat_abs(simulate_float sfloat)
{
        return sfloat &= ~SYMBOL_BIT;
}

void sfloat_get_components(simulate_float sfloat, simulate_float* base, simulate_float* symbol, signed char* exponent)
{
        if (exponent) {
                *exponent = (sfloat & EXPONENT_BITS) >> 23;
                *exponent = (*exponent ^ (1 << 7)) + 1;
        }
        if (symbol)
                *symbol = sfloat & SYMBOL_BIT;
        if (base)
                *base = (sfloat & ~(SYMBOL_BIT | EXPONENT_BITS)) | INTEGER_BIT;
}
