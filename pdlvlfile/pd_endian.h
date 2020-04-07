#ifndef PD_ENDIAN_H
#define PD_ENDIAN_H

/**
*   @file pd_endian.h
*   Header file for PD endian swapping functions
*  
*   This API supports swapping the endianness of integral values
*   based on the system's endianness.
*/

/**
*   @defgroup endian   Endian swapping functions
*   These functions convert integers from one endian to another.
*
*   Endian functions are named using the syntax pdlvl_XXtoYY,
*   where @a XX and @a YY are @b n, @b le32, @b le16, or @b be32.
*   The integer passed to a function is presumed to be @a XX and
*   is converted to @a YY. Here is an example.
*
*   @code
*       // native to 32 bit little endian
*       uint32_t native = 0x01020304;
*       uint32_t little_endian = pdlvl_ntole32(native);
*       
*       // native to 32 bit big endian
*       uint32_t native = 0x01020304;
*       uint32_t big_endian = pdlvl_ntobe32(native);
*   @endcode
*
*   The first example shown converts a native integer to little endian.
*   Because my machine is little endian, no conversion is done to @a native.
*   However, when it is converted to big endian, it turns from 0x01020304
*   to 0x04030201.
*/

#include <pd_stdinc.h>

/* system-dependent header file */
#ifdef pdlvlfile_EXPORTS
    #ifdef __linux
        #include "endian/linux/_pd_endian.h"
    #else
        #include "endian/windows/_pd_endian.h"
    #endif
    #include "pd_config.h"
#else
    #include <_pd_endian.h>
#endif

#ifndef LITTLE_ENDIAN
    #define LITTLE_ENDIAN   1234
#endif

#ifndef BIG_ENDIAN
    #define BIG_ENDIAN      4321
#endif

#ifndef UNKNOWN_ENDIAN
    #define UNKNOWN_ENDIAN  -1
#endif

/* C function declarations */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if !defined(__linux)
    extern uint16_t _pdlvl_swap16(uint16_t x);
    /// Swaps a 16 bit integer.
    #define pdlvl_swap16(x) _pdlvl_swap16(x)
#else
    #define pdlvl_swap16(x) (x)
#endif

#if !defined(__linux)
    extern uint32_t _pdlvl_swap32(uint32_t x);
    /// Swaps a 32 bit integer.
    #define pdlvl_swap32(x) _pdlvl_swap32(x);
#else
    #define pdlvl_swap32(x) (x)
#endif

/** Converts a 16 bit integer to little endian from the native byte order.
*
*   @param  x   An integer in native byte order.
*   @return     An integer converted to little endian.
*   @ingroup    endian
*/
extern uint16_t pdlvl_ntole16(uint16_t x);

/** Converts a 32 bit integer to little endian from the native byte order.
* 
*   @param  x   A 32-bit integer in native byte order
*   @return     The integer swapped to be little endian
*   @ingroup    endian
*/
extern uint32_t pdlvl_ntole32(uint32_t x);

/** Converts a 32 bit integer to big endian from the native byte order.
*
*   @param  x   A 32-bit integer in native byte order
*   @return     The integer swapped to be big endian
*   @ingroup    endian
*/
extern uint32_t pdlvl_ntobe32(uint32_t x);

/** Converts a 16 bit integer to the native byte order from little endian.
*
*   @param  x   A 16-bit integer in little endian format
*   @return     The integer converted to native endian format
*   @ingroup    endian
*/
extern uint16_t pdlvl_le16ton(uint16_t x);

/** Converts a 32 bit integer to the native byte order from little endian.
*
*   @param  x   A 32 bit integer in little endian format
*   @return     The integer converted to native byte order
*   @ingroup    endian
*/
extern uint32_t pdlvl_le32ton(uint32_t x);

/** Converts a 32 bit integer to the native byte order from big endian.
*
*   @param  x   A 32 bit integer in big endian format
*   @return     The integer converted to native byte order
*   @ingroup    endian
*/
extern uint32_t pdlvl_be32ton(uint32_t x);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_ENDIAN_H */
