#ifndef PD_STRING_H
#define PD_STRING_H

/**
*   @file   pd_string.h
*   C Header that defines portable string functions.
*/

#include "pd_config.h"

#ifdef HAVE_STRCHR
    /** Locates the first occurrence of @a c in a string.
    *
    *   @param  s   A C-style string.
    *   @param  c   The character to be located. It
    *               is passed as an @c int but is internally
    *               cast back to a @c char for comparison.
    *   @return     A pointer to the first occurrence of
    *               @a c in @a s.
    */
    #define pdlvl_strchr(s, c)  strchr(s, c)
#else
    #define pdlvl_strchr(s, c)
#endif

#ifdef HAVE_STRTOK
    /** Splits a string into tokens. Calls strtok(). */
    #define pdlvl_strtok(s, ss) strtok(s, ss)
#endif

#ifdef HAVE_STRLEN
    /** Measures the length of a string. Calls strlen(). */
    #define pdlvl_strlen(s)     strlen(s)
#endif

#ifdef HAVE_STRCPY
    /** Copies a string pointed to by @a s into the array pointed to by @a d.
    */
    #define pdlvl_strcpy(s, d)  strcpy(s, d)
#endif

#ifdef HAVE_STRCAT
    /** Appends a copy of the source string to the destination string.
    *   The first null character in @a d is overwritten by the first
    *   character in @a s. And a null character is included at the
    *   end of the new string formed by the concatenation of both @a d.
    *
    *   @return @a D is returned.
    */
    #define pdlvl_strcat(d, s)  strcat(d, s)
#endif

#ifdef HAVE_ISPUNCT
    /** Checks whether a character is a punctuation character.
    *
    *   @return Non-zero if @a c is a punctuation character
    *           (i.e., a graphical character but not an
    *           alphanumeric character), or zero otherwise.
    */
    #define pdlvl_ispunct(c)    ispunct(c)
#endif

#ifdef HAVE_ISDIGIT
    /** Checks whether a character is a digit.
    *
    *   @return Non-zero if @a c is a digit (0-9)
    *           or zero otherwise.
    */
    #define pdlvl_isdigit(c)        isdigit(c)
#endif

#define pdlvl_atoi(s)           atoi(s)

#endif /* PD_STRING_H */

