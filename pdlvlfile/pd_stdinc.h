#ifndef PD_STDINC_H_INCLUDED
#define PD_STDINC_H_INCLUDED

/* C++ headers if using C++ */
#ifdef __cplusplus
 #include <cstdio>
 #include <cstdlib>
 #include <cstring>
 #include <cerrno>
 #include <cstdint>
 #include <cstddef>
#else
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <errno.h>
 #include <stdbool.h>
 #include <stdint.h>
 #include <stddef.h>
#endif /* __cplusplus */

#endif /* PD_STDINC_H_INCLUDED */
