#ifndef PD_ENDIAN_H
#define PD_ENDIAN_H

#include <pd_stdinc.h>

/* system-dependent header file */
#ifdef pdlvlfile_EXPORTS
    #if defined(LINUX)
        #include "endian/linux/_pd_endian.h"
    #else
        #include "endian/windows/_pd_endian.h"
    #endif
#else
    #include <_pd_endian.h>
#endif

#ifndef LITTLE_ENDIAN
    #define LITTLE_ENDIAN 1234
#endif

#ifndef BIG_ENDIAN
    #define BIG_ENDIAN 4321
#endif

#ifndef UNKNOWN_ENDIAN
    #define UNKNOWN_ENDIAN -1
#endif

/* C function declarations */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
_pdlvl_swap16 - swap a 16-bit value
    @param x    an integer
    @return     x with its bytes reversed
*/
#if ! defined(__linux) || defined(KEEP_SWAP_FUNCTIONS)
    extern uint16_t _pdlvl_swap16(uint16_t x);
    #define pdlvl_swap16(x) _pdlvl_swap16(x);
#else
    #define pdlvl_swap16(x) (x)
#endif

/*
_pdlvl_swap32 - swap a 32-bit value
    @param x    integer to swap
    @return     swapped integer
*/
#if ! defined(__linux) || defined(KEEP_SWAP_FUNCTIONS)
    extern uint32_t _pdlvl_swap32(uint32_t x);
    #define pdlvl_swap32(x) _pdlvl_swap32(x);
#else
    #define pdlvl_swap32(x) (x)
#endif

/*
pdlvl_ntole16 - converts a native-endian 16-bit integer to little-endian
    @param x    an integer in native byte order
    @return     an integer in little-endian byte order
*/
extern uint16_t pdlvl_ntole16(uint16_t x);

/*
pdlvl_ntole32 - converts a native-endian 32-bit integer to little-endian
    @param x    an integer in native byte order
    @return     an integer in little-endian byte order
*/
extern uint32_t pdlvl_ntole32(uint32_t x);

/*
pdlvl_ntole32 - converts a native-endian 32-bit integer to little-endian
    @param x    an integer in native byte order
    @return     an integer in little-endian format
*/
extern uint32_t pdlvl_ntobe32(uint32_t x);

/*
pdlvl_le16ton - converts a little-endian 16-bit integer to native byte order
    @param x    an integer in little endian order
    @return     an integer in native byte order
*/
extern uint16_t pdlvl_le16ton(uint16_t x);

/*
pdlvl_le32ton - converts a little-endian 32-bit integer to native byte order
    @param x    little-endian integer
    @return     integer in native byte order
*/
extern uint32_t pdlvl_le32ton(uint32_t x);

/*
pdlvl_le32ton - converts a little-endian 32-bit integer to native byte order
    @param x    an integer in little-endian order
    @return     an integer in native byte order
*/
extern uint32_t pdlvl_be32ton(uint32_t x);

/*
pdlvl_be32ton - converts a big-endian 32-bit integer to native byte order
    @param x    an integer in big-endian order
    @return     an integer in native byte order
*/
extern uint32_t pdlvl_be32ton(uint32_t x);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_ENDIAN_H */
