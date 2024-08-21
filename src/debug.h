#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "constants.h"

void _assert_impl(bool expr, const char* expr_str, const char* file, uint32_t line)
{
    if (expr) return;
    fprintf(stderr, "Assertion failed, expected %s to be true @ %s, line %i\n", expr_str, file, line);
    exit(1);
}

#ifdef DEBUG
# define assert(expr) _assert_impl(expr, #expr, __FILE__, __LINE__)
# else
# define assert(expr) ;
# endif
