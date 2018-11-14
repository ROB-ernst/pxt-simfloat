#include "pxt.h"
#include "simulate_float.h"

namespace sfloat {

    /**
    * Perform soft-float conversion
    */
    //% blockId=sfloat_IntToSFloat block="Convert integer %x to SoftFloat representation"
    int IntToSFloat(int x) {
        simulate_float res = int_to_sfloat(x);
		return res;
    }

}
