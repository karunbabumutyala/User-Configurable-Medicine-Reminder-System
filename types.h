                      /* types.h */
#ifndef __TYPES_H__
#define __TYPES_H__

/*---------------------------------------------------------
    User Defined Data Types
----------------------------------------------------------

    These typedefs are used to simplify programming and
    improve code readability in embedded systems.

    Commonly used in:
    - LPC2148 projects
    - Drivers
    - Peripheral interfacing
    - Embedded applications

----------------------------------------------------------*/


/*---------------------------------------------------------
    8-bit Data Types
----------------------------------------------------------*/

// Unsigned 8-bit data type
// Range : 0 to 255
typedef unsigned char u8;

// Signed 8-bit data type
// Range : -128 to +127
typedef signed char s8;


/*---------------------------------------------------------
    16-bit Data Types
----------------------------------------------------------*/

// Unsigned 16-bit data type
// Range : 0 to 65535
typedef unsigned short int u16;

// Signed 16-bit data type
// Range : -32768 to +32767
typedef signed short int s16;


/*---------------------------------------------------------
    32-bit Data Types
----------------------------------------------------------*/

// Unsigned 32-bit data type
// Range : 0 to 4294967295
typedef unsigned int u32;

// Signed 32-bit data type
// Range : -2147483648 to +2147483647
typedef signed int s32;


/*---------------------------------------------------------
    Floating Point Data Types
----------------------------------------------------------*/

// 32-bit floating point type
// Used for decimal values
typedef float f32;


// 64-bit floating point type
// Higher precision decimal values
typedef double f64;

#endif

