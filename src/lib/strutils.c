#include "strutils.h"

bool is_whitespace(char c) {
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

inline bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

int parse_int(const char* str)
{
    int total = 0;

    char c;
    while ((c = *(str++)) && is_digit(c))
    {
        total = total * 10 + c - '0';
    }

    return total;
}