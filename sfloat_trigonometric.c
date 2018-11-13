/*
 * Version: 0.9
 * Author: Han, He <he.han@intel.com>
 * Date: Jan 6th, 2014
 */
#include "simulate_float.h"

#define PI_M2    0x40c90fdb // 2*Pi
#define PI_M3_D2 0x4096cbe4 // 3*Pi/2
#define PI       0x40490fdb // Pi
#define PI_D2    0x3fc90fdb // Pi/2
#define PI_D4    0x3f490fdb // Pi/4

#define FACTOR       0x3f1b74ee      // 0.6072529351
#define X_START      536870912       // 0x20000000 = (1 << 29)
#define SYMBOL_BIT   (0x01 << 31)
#define INTEGER_BIT  (1 << 23)

/* base_radians[i] = arctan(1/2^i) * 2^29 */
static const s32 base_radians[31] = {
        421657428,
        248918915,
        131521918,
        66762579,
        33510843,
        16771758,
        8387925,
        4194219,
        2097141,
        1048575,
        524288,
        262144,
        131072,
        65536,
        32768,
        16384,
        8192,
        4096,
        2048,
        1024,
        512,
        256,
        128,
        64,
        32,
        16,
        8,
        4,
        2,
        1,
        0
};

/* radians: must between 0 and Pi/4
 * cosine: indicate the value of cosine(radians)
 * sine: indicate the value of sine(radians)
 * tangent: indicate the value of tangent(radians)
 */
void sfloat_get_trigonometric(simulate_float radians, simulate_float* cosine, simulate_float* sine, simulate_float* tangent)
{
        simulate_float raw_base, symbol, sine_base, cosine_base, sine_symbol = 0, cosine_symbol = 0;
        signed char exponent, sine_exponent, cosine_exponent;
        s32 base, x = X_START, y = 0, x1, y1;
        s16 i;

        /* radians less than 0 */
        while ((int)(radians & SYMBOL_BIT))
                radians = sfloat_add(radians, PI_M2);
        while (sfloat_compare(radians, PI_M2) != SFLOAT_LESS_THAN)
                radians = sfloat_minus(radians, PI_M2);

        /* transfer radians to 0 ~ pi/4 */
        if (sfloat_compare(radians, PI_M3_D2) != SFLOAT_LESS_THAN) {
                radians = sfloat_minus(PI_M2, radians);
                sine_symbol = SYMBOL_BIT;
        } else if (sfloat_compare(radians, PI) != SFLOAT_LESS_THAN) {
                radians = sfloat_minus(radians, PI);
                sine_symbol = SYMBOL_BIT;
                cosine_symbol = SYMBOL_BIT;
        } else if (sfloat_compare(radians, PI_D2) != SFLOAT_LESS_THAN) {
                radians = sfloat_minus(PI, radians);
                cosine_symbol = SYMBOL_BIT;
        }

        sfloat_get_components(radians, &raw_base, &symbol, &exponent);

        /* -5 ~ 0 and -127 ~ -7 float use bit 23 as highest, but we use bit 29 (base on 0 ~ 31) */
        if (exponent >= -6)
                base = (raw_base << (exponent + 6));
        else if (exponent < -6)
                base = (raw_base >> (-exponent - 6));

        for (i = 0; i < 24; i++) {
                if (base > 0) {
                        x1 = (x - (y >> i));
                        y1 = (y + (x >> i));
                        base -= base_radians[i];
                } else {
                        x1 = (x + (y >> i));
                        y1 = (y - (x >> i));
                        base += base_radians[i];
                }
                x = x1;
                y = y1;
        }

        if (x < 0)
                x = -x;
        if (y < 0)
                y = -y;

        /* convert to sfloat then divide by X_START(2^29) */
        sine_base = int_to_sfloat(y);
        cosine_base = int_to_sfloat(x);

        if (sine != NULL) {
                sfloat_get_components(sine_base, &sine_base, NULL, &sine_exponent);
                sine_exponent -= 29;
                sine_exponent = (sine_exponent ^ (1 << 7)) - 1;
                sine_base &= ~INTEGER_BIT;
                sine_base = sine_base | (*(unsigned char *)&sine_exponent) << 23 | sine_symbol;
                *sine = sfloat_multiply(sine_base, FACTOR);
        }

        if (cosine != NULL) {
                sfloat_get_components(cosine_base, &cosine_base, NULL, &cosine_exponent);
                cosine_exponent -= 29;
                cosine_exponent = (cosine_exponent ^ (1 << 7)) - 1;
                cosine_base &= ~INTEGER_BIT;
                cosine_base = cosine_base | (*(unsigned char *)&cosine_exponent) << 23 | cosine_symbol;
                *cosine = sfloat_multiply(cosine_base, FACTOR);
        }

        if (tangent != NULL) {
                *tangent = sfloat_divide(sine_base, cosine_base) | (sine_symbol ^ cosine_symbol);
        }
}

simulate_float sfloat_sin(simulate_float radians)
{
        simulate_float result;

        sfloat_get_trigonometric(radians, NULL, &result, NULL);
        return result;
}

simulate_float sfloat_cos(simulate_float radians)
{
        simulate_float result;

        sfloat_get_trigonometric(radians, &result, NULL, NULL);
        return result;
}

simulate_float sfloat_tan(simulate_float radians)
{
        simulate_float result;

        sfloat_get_trigonometric(radians, NULL, NULL, &result);
        return result;
}

#define POSITIVE_ONE     0x3f800000
#define NEGATIVE_ONE     0xbf800000
#define TAN_MAX_POSITIVE 0x4c0d24d0 // 37000000.0
#define TAN_MAX_NEGATIVE 0xcc0d24d0

enum sfloat_inverse_trigonometric_flag {
        SFLOAT_ARCSIN,
        SFLOAT_ARCCOS,
        SFLOAT_ARCTAN,
};

simulate_float sfloat_get_inverse_trigonometric(simulate_float value, enum sfloat_inverse_trigonometric_flag flag)
{
        simulate_float raw_base, symbol, angle;
        signed char exponent;
        long long x, y, x1, y1;
        s32 radians = 0;
        s16 i;

        if (flag == SFLOAT_ARCSIN || flag == SFLOAT_ARCCOS) {
                /* the input value is error */
                if (sfloat_compare(value, POSITIVE_ONE) == SFLOAT_GREATER_THAN) {
                        return SFLOAT_POSITIVE_NAN;
                } else if (sfloat_compare(value, NEGATIVE_ONE) == SFLOAT_LESS_THAN) {
                        return SFLOAT_NEGATIVE_NAN;
                }
        } else {
                if (sfloat_compare(value, TAN_MAX_POSITIVE) == SFLOAT_GREATER_THAN) {
                        return PI_D2;
                } else if (sfloat_compare(value, TAN_MAX_NEGATIVE) == SFLOAT_LESS_THAN) {
                        return PI_D2 | SYMBOL_BIT;
                }
        }

        sfloat_get_components(value, &raw_base, &symbol, &exponent);
        /* -5 ~ 0 and -127 ~ -7 float use bit 23 as highest, but we use bit 29 (base on 0 ~ 31) */
        y = raw_base;
        if (exponent >= -6)
                y = (y << (exponent + 6));
        else if (exponent < -6)
                y = (y >> (-exponent - 6));
        if ((int)symbol)
                y = -y;

        if (flag == SFLOAT_ARCSIN || flag == SFLOAT_ARCCOS) {
                value = sfloat_sqrt(sfloat_minus(POSITIVE_ONE, sfloat_multiply(value, value)));
                sfloat_get_components(value, &raw_base, &symbol, &exponent);
                /* -5 ~ 0 and -127 ~ -7 float use bit 23 as highest, but we use bit 29 (base on 0 ~ 31) */
                x = raw_base;
                if (exponent >= -6)
                        x = (x << (exponent + 6));
                else if (exponent < -6)
                        x = (x >> (-exponent - 6));
                if ((int)symbol)
                        x = -x;
        } else {
                x = X_START;
        }

        for (i = 0; i < 24; i++) {
                if (y >= 0) {
                        x1 = (x + (y >> i));
                        y1 = (y - (x >> i));
                        radians += base_radians[i];
                } else {
                        x1 = (x - (y >> i));
                        y1 = (y + (x >> i));
                        radians -= base_radians[i];
                }
                x = x1;
                y = y1;
        }

        if (flag == SFLOAT_ARCCOS)
                radians = 0x3243F6A9 - radians;

        angle = int_to_sfloat(radians);
        sfloat_get_components(angle, &angle, &symbol, &exponent);
        exponent -= 29;
        exponent = (exponent ^ (1 << 7)) - 1;
        angle &= ~INTEGER_BIT;
        angle = angle | (*(unsigned char *)&exponent) << 23 | symbol;

        return angle;
}

simulate_float sfloat_asin(simulate_float value)
{
        return sfloat_get_inverse_trigonometric(value, SFLOAT_ARCSIN);
}

simulate_float sfloat_acos(simulate_float value)
{
        return sfloat_get_inverse_trigonometric(value, SFLOAT_ARCCOS);
}

simulate_float sfloat_atan(simulate_float value)
{
        return sfloat_get_inverse_trigonometric(value, SFLOAT_ARCTAN);
}

simulate_float sfloat_atan2(simulate_float y, simulate_float x)
{
        simulate_float result;

        result = sfloat_get_inverse_trigonometric(sfloat_divide(y, x), SFLOAT_ARCTAN);

        if (!(y & SYMBOL_BIT) && (x & SYMBOL_BIT))
                return sfloat_add(PI, result);
        else if ((y & SYMBOL_BIT) && (x & SYMBOL_BIT))
                return sfloat_minus(result, PI);

        return result;
}
