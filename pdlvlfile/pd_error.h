#ifndef PD_ERROR_H_INCLUDED
#define PD_ERROR_H_INCLUDED

/**
*   @file   pd_error.h
*
*   A header file for the pdlvlfile library. Contains
*   functions that set and retrieve error messages.
*/

/**
*   @defgroup   errors  Error diagnostics
*   Functions that set and get error messages.
*/

#ifdef PDLVL_INTERNAL
 #include "pd_stdinc.h"
 #include "pd_stddef.h"
#else
 #include <pd_stdinc.h>
 #include <pd_stddef.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** Formats an error string, which can be retrieved with pdlvl_geterror().
*
*   @param  fmt The format of the string, forwarded to vsprintf.
*   @param  ... A list of arguments corresponding to the format string, forwarded to vsprintf.
*
*   @ingroup    errors
*/
extern void pdlvl_seterror(const char* fmt, ...);

/** Formats a "bad parameter" error string. Calls pdlvl_seterror().
*
*   @ingroup    errors
*/
#define pdlvl_badparam(str)     pdlvl_seterror("%s : bad parameter '%s'", __FUNCTION__, str);

/** Formats an "out of memory" error string. Calls pdlvl_seterror().
*
*   @ingroup    errors
*/
#define pdlvl_outofmemory()     pdlvl_seterror("ran out of memory");

/** Formats a "write operation" error string. Calls pdlvl_seterror().
*
*   @ingroup    errors
 */
#define pdlvl_writeerror()      pdlvl_seterror(strerror(errno));

/** Returns the error string.
*
*   @return     The error string set by the last call to
*               pdlvl_seterror().
*   @ingroup    errors
*/
const char* pdlvl_geterror() ATTR_PURE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_ERROR_H_INCLUDED */
