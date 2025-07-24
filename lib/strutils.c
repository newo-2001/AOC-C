#include "strutils.h"

#include <string.h>

bool is_whitespace(char c)
{
    switch (c)
    {
    case ' ':
    case '\t':
    case '\r':
    case '\n':
        return true;
    default:
        return false;
    }
}

const char *skip_str(const char *source, const char *str)
{
    if (strstr(source, str) == source)
    {
        return source + strlen(str);
    }
    else
    {
        return NULL;
    }
}
