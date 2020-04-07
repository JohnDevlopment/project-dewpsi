#ifndef _MEMORY_H
#define _MEMORY_H

#define HAVE_STDLIB_H
#define HAVE_STDIO_H

#undef HAVE_MALLOC
#define HAVE_MALLOC

#undef HAVE_CALLOC
#define HAVE_CALLOC

#undef HAVE_FREE
#define HAVE_FREE

#undef HAVE_ABORT
#define HAVE_ABORT

#ifdef HAVE_STDLIB_H
    #include <stdlib.h>
#else
    #error Could not find stdlib.h!
#endif

#ifdef HAVE_STDIO_H
    #include <stdio.h>
#else
    #error Could not find stdio.h!
#endif

#ifdef HAVE_ABORT
    #define libmemory_abort() abort()
#else
    #error abort() not found!
#endif

/* Refers to the standard C calloc() function. */
void * libmemory_calloc(size_t nmemb, size_t size);

/* Refers to the standard C malloc() function. */
void * libmemory_malloc(size_t size);

/* Refers to the standard C free() function. */
void libmemory_free(void * ptr);

#endif /* _MEMORY_H */
