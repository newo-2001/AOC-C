#ifndef AOC_SLICE_H
#define AOC_SLICE_H

#include <stddef.h>
#include <stdbool.h>

/// @brief A view into a string, it is *not* null-terminated and *not* managed.
/// The string it is a view into must remaining valid for the lifetime of the slice.
typedef struct str_t
{
    const char* data;
    size_t length;
} str_t;

/// @brief Creates a slice from a null-terminated string.
/// @return A slice up-to (but excluding) the null-terminator.
str_t str_from_cstr(const char* str);

#define SLICE(x)                                                                                                       \
    (_Generic(x, const char*: str_from_cstr, char*: str_from_cstr, char[sizeof(x)]: str_from_cstr))((const char*)(x))

/// @brief Creates an iterator over a `str`.
static inline const char* str_begin(str_t str) { return str.data; }

/// @brief Advances the given iterator.
static inline const char* str_next(const char* it) { return ++it; }

/// @brief Returns a pointer beyond the last element in `str`.
static inline const char* str_end(str_t str) { return str.data + str.length; }

/// @brief Returns the character at `index` in `str`.
/// @note Requires `index < str.length`.
char str_at(str_t str, size_t index);

/// @brief Compares slice `a` with slice `b`.
/// @return A negative number if `a < b`, a positive number if `a > b` or 0 if they are equal.
int str_cmp(str_t a, str_t b);

/// @brief Creates a subslice out of an existing slice.
/// @param slice The slice to create a subslice from.
/// @param start The offset into the slice where the substring begins (inclusive) (0-indexed).
/// @param end The offset into the slice where the substring ends (exclusive) (0-indexed).
/// @return The sublice `slice[start:end)`.
/// @note The function requires `start <= end < str.length`.
str_t str_sub(str_t str, size_t start, size_t end);

/// @brief Searches the `haystack` for the first occurance of `needle`.
/// @param haystack The string to search in.
/// @param needle The substring to search for.
/// @param out_offset An out parameter that will contain the offset into `haystack`.
/// where `needle` was first found.
/// If the function returned `false` its value is undefined.
/// @return Whether the `haystack` contained `needle`.
bool str_find(str_t haystack, str_t needle, size_t* out_offset);

/// @brief Tests if `haystack` contain `needle`.
/// @param haystack The string to search in.
/// @param needle The substring to search for.
/// @return `true` if `haystack` contains `needle`, `false` otherwise.
bool str_contains(str_t haystack, str_t needle);

/// @brief Tests if `str` starts with `token`.
bool str_starts_with(str_t str, str_t token);

/// @brief Tests if `str` ends with `token`.
bool str_ends_with(str_t str, str_t token);

/// @brief An iterator that can be passed to `str_split_next`
/// to yield the next token of a `str_split` operation.
typedef struct StrSpliterator
{
    str_t str;
    str_t delimiter;
} StrSpliterator;

/// @brief Creates an iterator that yields subslices of `str` that are seperated by `delimiter`.
/// @returns A `StrSpliterator` which can be passed to `str_split_next` to yield the next token.
StrSpliterator str_split(str_t str, str_t delimiter);

/// @brief Creates an iterator that yields the lines in `str`.
/// @returns A `StrSpliterator` which can be passed to `str_split_next`.
StrSpliterator str_lines(str_t str);

/// @brief Attempts to extract the next token from `it`.
/// The extracted token is written into the `out_token` parameter.
/// If the function returned `false`, the value of `out_token` is undefined.
/// @returns `true` if a token was successfully extracted, or `false` if the end of the slice was reached.
bool str_split_next(StrSpliterator* it, str_t* out_token);

/// @brief Attempts to parse `str` as an integer.
/// It matches the regex `-?(\d+)`.
/// The result is written to `out_result`.
/// If the function returned `false`, the value of `out_result` is undefined.
/// @returns Whether the parsing succeeded.
bool str_parse_int(str_t str, int* out_result);

#endif