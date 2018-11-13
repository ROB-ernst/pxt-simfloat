#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
#ifndef NULL
#define NULL 0
#endif

typedef unsigned long long u64;
typedef signed long long s64;
#define BITMASK_64
#ifdef BITMASK_64
typedef u64 bitmask_t;
#else
typedef unsigned int bitmask_t;
#endif

#endif