#ifndef _SFLOAT_CONST_H_
#define _SFLOAT_CONST_H_

/* To get the const (in HOST):
 * float value = your_value;
 * printf("%x", *(simluate_float)&value);
 */
#define SFLOAT_CONST_N10      (0xc1200000) //-10
#define SFLOAT_CONST_N9       (0xc1100000) //-9
#define SFLOAT_CONST_N8       (0xc1000000) //-8
#define SFLOAT_CONST_N7       (0xc0e00000) //-7
#define SFLOAT_CONST_N6       (0xc0c00000) //-6
#define SFLOAT_CONST_N5       (0xc0a00000) //-5
#define SFLOAT_CONST_N4       (0xc0800000) //-4
#define SFLOAT_CONST_N3       (0xc0400000) //-3
#define SFLOAT_CONST_N2       (0xc0000000) //-2
#define SFLOAT_CONST_N1       (0xbf800000) //-1
#define SFLOAT_CONST_0        (0x0) //0
#define SFLOAT_CONST_1        (0x3f800000) //1
#define SFLOAT_CONST_2        (0x40000000) //2
#define SFLOAT_CONST_3        (0x40400000) //3
#define SFLOAT_CONST_4        (0x40800000) //4
#define SFLOAT_CONST_5        (0x40a00000) //5
#define SFLOAT_CONST_6        (0x40c00000) //6
#define SFLOAT_CONST_7        (0x40e00000) //7
#define SFLOAT_CONST_8        (0x41000000) //8
#define SFLOAT_CONST_9        (0x41100000) //9
#define SFLOAT_CONST_10       (0x41200000) //10

#define SFLOAT_CONST_PI       (0x40490fdb) // Pi
#define SFLOAT_CONST_PI_M2    (0x40c90fdb) // 2*Pi
#define SFLOAT_CONST_PI_M3_D2 (0x4096cbe4) // 3*Pi/2
#define SFLOAT_CONST_PI_D2    (0x3fc90fdb) // Pi/2
#define SFLOAT_CONST_PI_D4    (0x3f490fdb) // Pi/4
#define SFLOAT_CONST_PI_M2_D3 (0x40060a92) // 2*Pi/3
#define SFLOAT_CONST_PI_D3    (0x3f860a92) // Pi/3

#define SFLOAT_CONST_DEG2RAD  (0x3c8efa35) // Pi/180
#define SFLOAT_CONST_RAD2DEG  (0x42652ee1) // 180/Pi

#endif
