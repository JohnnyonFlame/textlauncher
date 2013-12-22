#include <cstdio>
#include <SDL.h>
#include "textscreen.h"

#include "common.h"

int systemf(const char *fmt, ...)
{
        char __sys[2048];
        int ret_code;
        va_list args;
        va_start(args, fmt);
                vsnprintf(__sys, 1023, fmt, args);
                ret_code = system(__sys);
        va_end(args);

        return ret_code;
}
