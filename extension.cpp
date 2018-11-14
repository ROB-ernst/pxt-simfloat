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
	//% blockId=sfloat_add block="Add two SoftFloats %x %y"
	int add(int x, int y)
	{
		return sfloat_add(x, y);
	}
	
    /**
    * Multiply two soft floats
    */
	//% blockId=sfloat_multiply block="Multiply %x and %y"
	int multiply(int x, int y)
	{
		return sfloat_multiply(x, y);
	}
	
    /**
    * Subtract two soft floats
    */
	//% blockId=sfloat_minus block="subtract %x from %y"
	int minus(int x, int y)
	{
		return sfloat_minus(x, y);
	}

	/**
    * Divide two soft floats
    */
	//% blockId=sfloat_div block="divide %x by %y"
	int div(int x, int y)
	{
		return sfloat_divide(x, y);
	}
}
