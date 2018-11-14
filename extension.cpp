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
  * Add two soft-floats
  */
	//% blockId=sfloat_add block="add %x and %y"
	int add(int x, int y)
	{
		return sfloat_add(x, y);
	}
	
  /**
  * Multiply two soft-floats
  */
	//% blockId=sfloat_add block="multiply %x %y"
	int multipy(int x, int y)
	{
		return sfloat_multiply(x, y);
	}
	
  /**
  * Subtract two soft-floats
  */
	//% blockId=sfloat_add block="subtract %y from %x"
	int minus(int x, int y)
	{
		return sfloat_minus(x, y);
	}
	
  /**
  * Divide two soft-floats
  */
	//% blockId=sfloat_add block="divide %x by %y"
	int div(int x, int y)
	{
		return sfloat_divide(x, y);
	}
}
