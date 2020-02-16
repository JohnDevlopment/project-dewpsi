#include "pdlvlfile.h"
#include <stdarg.h>

static char _error[50];

void pdlvl_seterror(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsprintf(_error, fmt, args);
    va_end(args);
}

const char* pdlvl_geterror()
{
    return _error;
}
