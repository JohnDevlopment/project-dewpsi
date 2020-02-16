#ifndef PD_ERROR_H_INCLUDED
#define PD_ERROR_H_INCLUDED

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

/* sets the current error message */
extern void pdlvl_seterror(const char* fmt, ...);
#define bad_param(str) pdlvl_seterror("%s : bad param '%s'", __FUNCTION__, str);
#define out_of_memory() pdlvl_seterror("ran out of memory");
#define write_error() pdlvl_seterror(strerror(errno));

/* returns the error string */
const char* pdlvl_geterror() ATTR_PURE;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PD_ERROR_H_INCLUDED */
