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
	//% blockId=sfloat_add block="[SF] add x %x|and y %y"
	int add(int x, int y)
	{
		return sfloat_add(x, y);
	}
	
		
	/**
    * Multiply two soft floats
    */
	//% blockId=sfloat_add_f block="[F] add x %x|and y %y"
	int multiply(int x, int y)
	{
		float c = ((float*)(&x)) + ((float*)(&y));
		return *((int *)(&c));
	}
	
    /**
    * Multiply two soft floats
    */
	//% blockId=sfloat_multiply block="[SF] multiply x %x|and y %y"
	int multiply(int x, int y)
	{
		return sfloat_multiply(x, y);
	}
	
	/**
    * Multiply two soft floats
    */
	//% blockId=sfloat_multiply_f block="[F] multiply x %x|and y %y"
	int multiply(int x, int y)
	{
		float c = ((float*)(&x)) * ((float*)(&y));
		return *((int *)(&c));
	}
	
    /**
    * Subtract two soft floats
    */
	//% blockId=sfloat_minus block="[SF] subtract y %y|from x %x"
	int minus(int x, int y)
	{
		return sfloat_minus(x, y);
	}
	
	/**
    * Subtract two soft floats
    */
	//% blockId=sfloat_minus_f block="[F] subtract y %y|from x %x"
	int multiply(int x, int y)
	{
		float c = ((float*)(&x)) - ((float*)(&y));
		return *((int *)(&c));
	}

	/**
    * Divide two soft floats
    */
	//% blockId=sfloat_div_f block="[F] divide x %x|by y %y"
	int div_float(int x, int y)
	{
		float c = (*((float *)&x)) / (*((float *)&y));
		return *((int *)(&c));
	}

    /**
    * Divide two soft floats
    */
	//% blockId=sfloat_div block="[SF] divide x %x|by y %y"
	int div(int x, int y)
	{
		return sfloat_divide(x,y);
	}
	
	/**
    * Get sine of a soft float
    */
	//% blockId=sfloat_sin block="[SF] sine of radians %x"
	int sin(int x)
	{
		return sfloat_sin(x);
	}
	
	/**
    * Get sine of a soft float
    */
	//% blockId=sfloat_sin_f block="[F] sine of radians %x"
	int sin(int x)
	{
		float c = sin(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get cosine of a soft float
    */
	//% blockId=sfloat_cos block="[SF] cosine of radians %x"
	int cos(int x)
	{
		return sfloat_cos(x);
	}
	
	/**
    * Get cosine of a soft float
    */
	//% blockId=sfloat_cos_f block="[F] cosine of radians %x"
	int sin(int x)
	{
		float c = cos(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get tangens of a soft float
    */
	//% blockId=sfloat_tan block="[SF] tangens of radians %x"
	int tan(int x)
	{
		return sfloat_tan(x);
	}
	
	/**
    * Get tangens of a soft float
    */
	//% blockId=sfloat_tan_f block="[F] tangens of radians %x"
	int tan(int x)
	{
		float c = tan(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get square root of a soft float
    */
	//% blockId=sfloat_sqrt block="[SF] sqrt of x %x"
	int sqrt(int x)
	{
		return sfloat_sqrt(x);
	}
	
	/**
    * Get square root of a soft float
    */
	//% blockId=sfloat_sqrt_f block="[F] sqrt of x %x"
	int sqrt(int x)
	{
		rfloat c = sqrt(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get arcus sine of a soft float
    */
	//% blockId=sfloat_asin block="[SF] arcsin of x %x"
	int asin(int x)
	{
		return sfloat_asin(x);
	}
	
	/**
    * Get arcus sine of a soft float
    */
	//% blockId=sfloat_asin_f block="[F] arcsin of x %x"
	int asin(int x)
	{
		rfloat c = asin(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get arcus cosine of a soft float
    */
	//% blockId=sfloat_acos block="[SF] arccos of x %x"
	int acos(int x)
	{
		return sfloat_acos(x);
	}
	
	/**
    * Get arcus cosine of a soft float
    */
	//% blockId=sfloat_acos_f block="[F] arccos of x %x"
	int acos(int x)
	{
		rfloat c = acos(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get arcus tangens of a soft float
    */
	//% blockId=sfloat_atan block="[SF] arctan of x %x"
	int atan(int x)
	{
		return sfloat_atan(x);
	}
	
	/**
    * Get arcus tangens of a soft float
    */
	//% blockId=sfloat_atan_f block="[F] arctan of x %x"
	int atan(int x)
	{
		rfloat c = atan(*((float *)&x));
		return *((int *)(&c));
	}
	
	/**
    * Get arcus tangens 2 of two soft float
    */
	//% blockId=sfloat_atan2 block="[SF] atan2 of y %y|and x %x"
	int atan2(int y, int x)
	{
		return sfloat_atan2(y, x);
	}
	
	/**
    * Get opposite of a soft float
    */
	//% blockId=sfloat_neg block="[SF] opposite of x %x"
	int neg(int x)
	{
		return (x ^ (1 << 31));
	}
}
