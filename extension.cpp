#include "pxt.h"
#include "simulate_float.h"

namespace sfloat {

    /**
    * Perform soft-float conversion
    */
    //% blockId=sfloat_fromInt block="Convert integer %x to SoftFloat representation"
    int fromInt(int x) {
        simulate_float res = int_to_sfloat(x);
		return res;
    }
}
