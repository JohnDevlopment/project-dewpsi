/*! @file   main.h
*   @author John Russell
*   @data   Sat Feb 29 07:02:24 CST 2020
*   @brief  Header that contains misc functions and macros used by this program.
*   
*   This header contains a wide range of macros along with a few (or the one) function.
*   Macros contained here include debug printing macros, those for range comparison,
*   casting, error checks, argument shifting, and event references to standard C
*   library functions.
*/
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "../pd_config.h"

#include <pdlvlfile.h>

typedef struct {
    int* ipVals;
    size_t szLen;
    char code;
} intArray;

typedef struct {
    FILE* fs;
    Level* lvl;
    LevelHeader hd;
    const char* file;
    const char* cmd;
    const char* opt;
    intArray vals;
} cmdlineInfo;

/*! @brief      Returns true if a value is within a range.
*   @param  val The value being compared.
*   @param  min Minimum value in a range.
*   @param  max Maximum value in a range.
*   @return     True if val is within range, false otherwise.
*/
#define cmp_rng(val, min, max)      ((val-1) < (max-min))

/* Debug macros */
#ifndef NDEBUG
    #define print_func(f)           printf("-- function: %s (%p)\n", #f, f)
    #define print_opt(o)            printf("-- option: %s\n", #o)
    #define print_int(v)            printf("-- variable: %s = %d\n", #v, v)
    #define print_uint(v)           printf("-- variable: %s = %u\n", #v, v)
    #define print_str(s)            printf("-- variable: %s = %s\n", #s, s)
    #define print_ptr(p)            printf("-- pointer: %s = %p\n", #p, p)
#else
    #define print_func(f)
    #define print_opt(o)
    #define print_int(v)
    #define print_uint(v)
    #define print_str(s)
    #define print_ptr(p)
#endif

/*! @brief          Shifts the argument list by one place.
*   @param  argc    \b argc variable.
*   @param  argv    \b argv variable.
*/
#define adv_arg(argc, argv)         --argc; \
                                    ++argv;

/*! @brief          Shifts the argument list by two places.
*   @param  argc    \b argc variable.
*   @param  argv    \b argv variable.
*/
#define adv_arg2(argc, argv)        argc -= 2; \
                                    argv += 2;

/*! @brief          Emits an error if an option has no argument to go with it.
*   @param  argc    Current argument count.
*   @param  arg     String containing the name of an option.
*   @note           This macro causes the current scope to return if an error is emitted.
*                   The value returned is 1.
*/
#define no_arg(argc, arg)           if ((argc-1) == 0) \
                                    { \
                                        fprintf(stderr, "not enough arguments for '%s'\n", arg); \
                                        return 1; \
                                    }

/*! A simple C-style cast. */
#define cast(type, expr)            (type)(expr)

/* C standard library functions */

#define pd_atexit(f)                atexit(f)
#define pd_calloc(nm, sz)           calloc(nm, sz)
#define pd_abort()                  abort()
#define pd_memcpy(dst, src, n)      memcpy(dst, src, n)
#define pd_memset(dst, val, sz)     memset(dst, val, sz)
#define pd_strcspn(str1, str2)      strcspn(str1, str2)
#define pd_strcpy(dst, src)         strcpy(dst, src)
#define pd_strncpy(dst, src, n)     strncpy(dst, src, n)
#define pd_strcmp(a, b)             strcmp(a, b)
#define pd_strrchr(str, c)          strrchr(str, c)
#define pd_strlen(str)              strlen(str)
#define pd_strstr(str1, str2)       strstr(str1, str2)
#define pd_atoi(str)                atoi(str)
#define pd_strtoul(str, end, base)  strtoul(str, end, base)
#define pd_strtol(str, end, base)   strtol(str, end, base)
#define pd_strtok(s1, s2)           strtok(s1, s2)
#define pd_isdigit(ch)              isdigit(ch)
#define pd_isxdigit(ch)             isxdigit(ch)

#define pd_fillzero(obj)            pd_memset(&obj, 0, sizeof(obj))

/* typecasting operators */

/*! Static casting of EXPR to type TYPE. */
#ifdef __cplusplus
    #define pd_static_cast(type, expr)  static_cast<type>(expr)
#else
    #define pd_static_cast(type, expr)  (type)(expr)
#endif /* __cplusplus */

/*! Casting of EXPR to TYPE, adding or removing const-ness. */
#ifdef __cplusplus
    #define pd_const_cast(type, expr)   const_cast<type>(expr)
#else
    #define pd_const_cast(type, expr)   (type)(expr)
#endif /* __cplusplus */

/*! @brief      Creates a hash from a string.
*   @param  str Input string.
*   @return     A 32-bit hash of the string.
*   @remark     It cannot be guarranteed that the returned hash won't
*               someday clash with another. But the purpose of this
*               function isn't for creating hashes for the sake of
*               hash tables, so that concern is moot.
*/
uint32_t makeHash(const char* str);

/*! @brief          Frees memory or appends to internal "free list".
*   @param  count   Number of pointers to add to internal list. If <= 0,
                    frees all current pointers in list.
*   @param  ...     COUNT number of pointers added to internal "free list".
*/
void freeMemory(int count, ...);

/*! @brief          Frees memory associated with a cmdlineInfo object and reinitializes its members to zero.
*   @param  info    A pointer to a cmdlineInfo; will not be freed.
*/
void delCmdInfo(cmdlineInfo* const info);

#endif /* MAIN_H_INCLUDED */
