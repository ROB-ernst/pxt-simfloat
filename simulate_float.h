/*
 * Version: 0.9.1
 * Author: Han, He <he.han@intel.com>
 * Date: Nov 21st, 2013
 * Update: Nov 27th, 2013 : Add cubic root function
 */
#ifndef _SIMULATE_FLOAT_H_
#define _SIMULATE_FLOAT_H_

#include "sfloat_const.h"
#include "sfloat_common.h"

#define SFLOAT_POSITIVE_INFINITY (0x7f800000)
#define SFLOAT_SFLOAT_NEGATIVE_INFINITY (0xff800000)
#define SFLOAT_POSITIVE_NAN      (0x7fc00000)
#define SFLOAT_NEGATIVE_NAN      (0xffc00000)
#define SFLOAT_POSITIVE_ZERO     (0x00000000)
#define SFLOAT_NEGATIVE_ZERO     (0x80000000)

enum sfloat_error_t {
        SFLOAT_ERR_NEGATIVE_INFINITY = -1,
        SFLOAT_ERR_SUCCESS = 0,
        SFLOAT_ERR_POSITIVE_INFINITY = 1,
        SFLOAT_ERR_NAN,
        SFLOAT_ERR_INTEGER_OVERFLOW,
};

enum sfloat_compare_t {
        SFLOAT_LESS_THAN = -1,
        SFLOAT_EQUAL_TO = 0,
        SFLOAT_GREATER_THAN = 1,
        SFLOAT_COMPARE_UNKNOWN,
};

typedef u32 simulate_float;

#define sfloat_opposite(a)    (a ^ (1 << 31))
#define sfloat_deg2rad(angle) (sfloat_multiply(angle, SFLOAT_CONST_DEG2RAD))
#define sfloat_rad2deg(angle) (sfloat_multiply(angle, SFLOAT_CONST_RAD2DEG))

simulate_float int_to_sfloat(int num);
enum sfloat_error_t sfloat_to_int(simulate_float sfloat, int *num);
simulate_float sfloat_add(simulate_float a, simulate_float b);
simulate_float sfloat_minus(simulate_float a, simulate_float b);
simulate_float sfloat_multiply(simulate_float a, simulate_float b);
simulate_float sfloat_divide(simulate_float a, simulate_float b);
simulate_float sfloat_sqrt(simulate_float sfloat);
simulate_float sfloat_cbrt(simulate_float sfloat);
simulate_float sfloat_abs(simulate_float sfloat);
enum sfloat_compare_t sfloat_compare(simulate_float a, simulate_float b);
void sfloat_get_components(simulate_float sfloat, simulate_float* base, simulate_float* symbol, signed char* exponent);
void sfloat_get_trigonometric(simulate_float radians, simulate_float* cosine, simulate_float* sine, simulate_float* tangent);
simulate_float sfloat_sin(simulate_float radians);
simulate_float sfloat_cos(simulate_float radians);
simulate_float sfloat_tan(simulate_float radians);
simulate_float sfloat_asin(simulate_float value);
simulate_float sfloat_acos(simulate_float value);
simulate_float sfloat_atan(simulate_float value);
simulate_float sfloat_atan2(simulate_float y, simulate_float x);
#endif
