#include "pd_stdinc.h"
#include "pd_string.h"
#include "main.h"

int string_ishex(const char* str)
{
    if (str[0] == '0' && str[1] == 'x')
    {
        /*++str;
        ++str;*/
        str += 2;
    }
    else
    {
        return false;
    }
    
    /* return false if a non-hex number is found */
    while (*str != '\0')
    {
        if (! pd_isxdigit(*str))
            return false;
        ++str;
    }
    
    return true;
}

size_t string_strcnt(const char* src, int ch)
{
    size_t result = 0;
    char cch = (char) ch;
    for (const char* pch = src; *pch != '\0'; ++pch)
    {
        if (*pch == cch)
        {
            ++result;
        }
    }
    
    return result;
}

unsigned long int string_strtoul(const char* str, char** endptr)
{
    unsigned long int ulVal;
    int iBase;
    
    /* base 16 (hex) or base 10 (decimal) integer */
    if (string_ishex(str))
        iBase = 16;
    else
        iBase = 10;
    
    /* convert string into integer */
    errno = 0;
    ulVal = pd_strtoul(str, endptr, iBase);
    
    if (errno)
    {
        if (ulVal != ULONG_MAX)
        {
            fprintf(stderr, "error converting string: %s\n", strerror(errno));
        }
        else
        {
            errno = 0;
        }
    }
    
    return ulVal;
}

long int string_strtol(const char* str, char** endptr)
{
    long int lVal;
    int iBase;
    
    /* base 16 (hex) or base 10 (decimal) integer */
    if (string_ishex(str))
        iBase = 16;
    else
        iBase = 10;
    
    /* convert string into integer */
    errno = 0;
    lVal = pd_strtol(str, endptr, iBase);
    
    if (errno)
    {
        if (lVal != LONG_MAX || lVal != LONG_MIN)
        {
            fprintf(stderr, "error converting string: %s\n", strerror(errno));
        }
    }
    
    return lVal;
}
