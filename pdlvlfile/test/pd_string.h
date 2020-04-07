/*! @file   pd_string.h
*   @brief  A header that contains string functions.
*   
*   This header contains functions that manipulate, search, and convert strings.
*/
#ifndef PD_STRING_H
#define PD_STRING_H

/*! @brief      Returns 1 if the string depicts a hexadecimal number.
*   @param  str The string to process.
*   @return     1 if the string depicts a hexadecimal integer or 0 otherwise.
*/
int string_ishex(const char* str);

/*! @brief  Counts how many of a certain character are in string.
*   @param  src String to search.
*   @param  ch  The character (cast to a char) to search for in <src>.
*   @return     Number of instances, if any, of <ch> that are in string.
*/
size_t string_strcnt(const char* src, int ch);

/*! @brief  Converts a string to an unsigned long integer.
*
*   @param  str     String containing valid decimal or hexadecimal digits.
*   @param  endptr  If set, fills a pointer with the address to after the last
*                   valid digit character.
*   @return         The integer converted from the string, ULONG_MAX if oveflow
*                   occurs, or ULONG_MIN if underflow occurs. In both cases, errno
*                   is set to ERANGE.
*/
unsigned long int string_strtoul(const char* str, char** endptr);

/*! @brief  Converts a string to a signed long integer.
*
*   @param  str     String containing valid decimal or hexadecimal digits.
*   @param  endptr  If set, fills a pointer with the address to after the last
*                   valid digit character.
*   @return         The integer converted from the string, LONG_MAX if oveflow
*                   occurs, or LONG_MIN if underflow occurs. In both cases, errno
*                   is set to ERANGE.
*/
long int string_strtol(const char* str, char** endptr);

#endif /* PD_STRING_H */
