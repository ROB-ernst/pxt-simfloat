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
	
	/**
    * Get sine of a soft float
    */
	//% blockId=sfloat_sin block="sine of radians %x"
	int sin(int x)
	{
		return sfloat_sin(x);
	}
	
	/**
    * Get cosine of a soft float
    */
	//% blockId=sfloat_cos block="cosine of radians %x"
	int cos(int x)
	{
		return sfloat_cos(x);
	}
	
	/**
    * Get tangens of a soft float
    */
	//% blockId=sfloat_sin block="tangens of radians %x"
	int tan(int x)
	{
		return sfloat_tan(x);
	}
	
	/**
    * Get square root of a soft float
    */
	//% blockId=sfloat_sin block="sqrt of x %x"
	int sqrt(int x)
	{
		return sfloat_sqrt(x);
	}
	
	/**
    * Get arcus sine of a soft float
    */
	//% blockId=sfloat_sin block="arcsin of x %x"
	int asin(int x)
	{
		return sfloat_asin(x);
	}
	
	/**
    * Get arcus cosine of a soft float
    */
	//% blockId=sfloat_sin block="arccos of x %x"
	int acos(int x)
	{
		return sfloat_acos(x);
	}
	
	/**
    * Get arcus tangens of a soft float
    */
	//% blockId=sfloat_atan block="arctan of x %x"
	int atan(int x)
	{
		return sfloat_atan(x);
	}
	
	/**
    * Get arcus tangens 2 of two soft float
    */
	//% blockId=sfloat_atan block="atan2 of y %y|and x %x"
	int atan(int y, int x)
	{
		return sfloat_atan2(y, x);
	}
	
	/**
    * Get opposite of a soft float
    */
	//% blockId=sfloat_neg block="opposite of x %x"
	int neg(int x)
	{
		return (x ^ (1 << 31));
	}
}
