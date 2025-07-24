#ifndef AOC_STRUTILS_H
#define AOC_STRUTILS_H

#include <stdbool.h>

bool is_whitespace(char c);

const char *skip_str(const char *source, const char *str);

static inline bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

#endif