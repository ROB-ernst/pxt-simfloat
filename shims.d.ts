// Auto-generated. Do not edit.
declare namespace sfloat {

    /**
     * Perform soft-float conversion
     */
    //% blockId=sfloat_fromInt block="Convert to SoftFloat %x" shim=sfloat::fromInt
    function fromInt(x: int32): int32;

    /**
     * Add two soft floats
     */
    //% blockId=sfloat_add block="Add two SoftFloats x %x|and y %y" shim=sfloat::add
    function add(x: int32, y: int32): int32;

    /**
     * Multiply two soft floats
     */
    //% blockId=sfloat_multiply block="Multiply x %x|and y %y" shim=sfloat::multiply
    function multiply(x: int32, y: int32): int32;

    /**
     * Subtract two soft floats
     */
    //% blockId=sfloat_minus block="subtract x %x|from y %y" shim=sfloat::minus
    function minus(x: int32, y: int32): int32;

    /**
     * Divide two integers
     */
    //% blockId=sfloat_div_float block="divide x %x|by y %y (using floats)" shim=sfloat::div_float
    function div_float(x: int32, y: int32): int32;

    /**
     * Divide two soft floats
     */
    //% blockId=sfloat_div block="divide x %x|by y %y" shim=sfloat::div
    function div(x: int32, y: int32): int32;

    /**
     * Get sine of a soft float
     */
    //% blockId=sfloat_sin block="sine of radians %x" shim=sfloat::sin
    function sin(x: int32): int32;

    /**
     * Get cosine of a soft float
     */
    //% blockId=sfloat_cos block="cosine of radians %x" shim=sfloat::cos
    function cos(x: int32): int32;

    /**
     * Get tangens of a soft float
     */
    //% blockId=sfloat_sin block="tangens of radians %x" shim=sfloat::tan
    function tan(x: int32): int32;

    /**
     * Get square root of a soft float
     */
    //% blockId=sfloat_sin block="sqrt of x %x" shim=sfloat::sqrt
    function sqrt(x: int32): int32;

    /**
     * Get arcus sine of a soft float
     */
    //% blockId=sfloat_sin block="arcsin of x %x" shim=sfloat::asin
    function asin(x: int32): int32;

    /**
     * Get arcus cosine of a soft float
     */
    //% blockId=sfloat_sin block="arccos of x %x" shim=sfloat::acos
    function acos(x: int32): int32;

    /**
     * Get arcus tangens of a soft float
     */
    //% blockId=sfloat_atan block="arctan of x %x" shim=sfloat::atan
    function atan(x: int32): int32;

    /**
     * Get arcus tangens 2 of two soft float
     */
    //% blockId=sfloat_atan2 block="atan2 of y %y|and x %x" shim=sfloat::atan2
    function atan2(y: int32, x: int32): int32;

    /**
     * Get opposite of a soft float
     */
    //% blockId=sfloat_neg block="opposite of x %x" shim=sfloat::neg
    function neg(x: int32): int32;
}

// Auto-generated. Do not edit. Really.
