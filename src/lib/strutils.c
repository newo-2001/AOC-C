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