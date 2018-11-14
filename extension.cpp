#include "pxt.h"
#include "simulate_float.h"

namespace sfloat {

    /**
    * Perform soft-float conversion
    */
    //% blockId=sfloat_fromInt block="Convert to SoftFloat %x"
    int fromInt(int x) {
        return int_to_sfloat(x);
    }
	
	//% blockId=sfloat_add block="Add two SoftFloats %x %y"
	int add(int x, int y)
	{
		return sfloat_add(x, y);
	}
	
	//% blockId=sfloat_add block="Multiply two SoftFloats %x %y"
	int multipy(int x, int y)
	{
		return sfloat_multiply(x, y);
	}
	
	//% blockId=sfloat_add block="Subtract two SoftFloats %x %y"
	int minus(int x, int y)
	{
		return sfloat_minus(x, y);
	}
	
	//% blockId=sfloat_add block="Divide two SoftFloats %x %y"
	int div(int x, int y)
	{
		return sfloat_divide(x, y);
	}
}
