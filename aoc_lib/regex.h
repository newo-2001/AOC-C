#ifndef AOC_REGEX_H
#define AOC_REGEX_H

#include "str.h"

typedef struct Regex Regex;

/// @brief Attempts to compile the given string into a regular expression
/// @param str The string to compile into a regex.
/// @param out_regex Out parameter for the regex
/// @return Whether the expression compiled successfully.
bool regex_compile(str_t str, Regex* out_regex);

/// @brief Will match a string against a regex and return a collection of captures.
/// @param regex The regex to match against.
/// @param options The string to attempt to match.
/// @return Whether the expression compiled successfully.
void regex_captures(Regex* regex, str_t str);

/// @brief Frees the resources allocated for the regex
void regex_destroy(Regex* regex);

#endif