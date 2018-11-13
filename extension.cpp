#include "pxt.h"
#include "simulate_float.h"

namespace sfloat {

    /**
    * Perform soft-float conversion
    */
    //% blockId=sfloat_IntToSFloat block="Integer to SoftFloat"
    int IntToSFloat(int x) {
        simulate_float res = int_to_sfloat(x);
		return res;
    }

}
