#ifndef AOC_STRUTILS_H
#define AOC_STRUTILS_H

#include "../constants.h"

bool is_whitespace(char c);

inline bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

#endif