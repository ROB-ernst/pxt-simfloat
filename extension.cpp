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
	
    /**
    * Add two soft floats
    */
	//% blockId=sfloat_add block="Add two SoftFloats x %x|and y %y"
	int add(int x, int y)
	{
		return sfloat_add(x, y);
	}
	
    /**
    * Multiply two soft floats
    */
	//% blockId=sfloat_multiply block="Multiply x %x|and y %y"
	int multiply(int x, int y)
	{
		return sfloat_multiply(x, y);
	}
	
    /**
    * Subtract two soft floats
    */
	//% blockId=sfloat_minus block="subtract x %x|from y %y"
	int minus(int x, int y)
	{
		return sfloat_minus(x, y);
	}

	/**
    * Divide two soft floats
    */
	//% blockId=sfloat_div block="divide x %x|by y %y"
	int div(int x, int y)
	{
		return sfloat_divide(x, y);
	}
}
