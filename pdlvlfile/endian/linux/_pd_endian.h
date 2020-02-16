#ifndef ENDIAN_H_INCLUDED
#define ENDIAN_H_INCLUDED

#ifdef __cplusplus
 #include <cstdio>
#else
 #include <stdint.h>
#endif /* __cplusplus */

/* linux-specific headers and definitions */
#define _BSD_SOURCE 1
#define _DEFAULT_SOURCE 1
#include <endian.h>

#endif /* ENDIAN_H_INCLUDED */
