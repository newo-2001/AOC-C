#include "str.h"

#include <string.h>
#include <assert.h>

#include "math.h"

str_t str_from_cstr(const char* str)
{
    return (str_t) {
        .data = str,
        .length = strlen(str),
    };
}

char str_at(str_t str, size_t index)
{
    assert(index < str.length);
    return str.data[index];
}

int str_cmp(str_t a, str_t b)
{
    int result = memcmp(a.data, b.data, min(a.length, b.length));
    return result == 0 ? (int) (a.length - b.length) : result;
}

str_t str_sub(str_t str, size_t start, size_t end)
{
    assert(end <= str.length);
    assert(start <= end);

    return (str_t) {
        .data = str.data + start,
        .length = end - start,
    };
}

bool str_find(str_t haystack, str_t needle, size_t* out_offset)
{
    if (needle.length > haystack.length) return false;

    if (needle.length == 0)
    {
        *out_offset = 0;
        return true;
    }

    size_t matching = 0;
    for (size_t i = 0; i < haystack.length; i++)
    {
        if (haystack.data[i] == needle.data[matching])
        {
            if (++matching == needle.length)
            {
                *out_offset = i + 1 - needle.length;
                return true;
            }
        }
        else
        {
            matching = haystack.data[i] == needle.data[0];
        }
    }

    return false;
}

bool str_contains(str_t haystack, str_t needle)
{
    size_t offset;
    return str_find(haystack, needle, &offset);
}

bool str_starts_with(str_t str, str_t token)
{
    str = str_sub(str, 0, token.length);
    return !str_cmp(str, token);
}

bool str_ends_with(str_t str, str_t token)
{
    if (token.length > str.length) return false;

    str = str_sub(str, str.length - token.length, str.length);
    return !str_cmp(str, token);
}

StrSpliterator str_split(str_t str, str_t delimiter)
{
    return (StrSpliterator) {
        .str = str,
        .delimiter = delimiter,
    };
}

StrSpliterator str_lines(str_t str)
{
    return str_split(str, STR_SLICE("\n"));
}

bool str_split_next(StrSpliterator* it, str_t* out_token)
{
    str_t str = it->str;

    if (str.length == 0) return false;

    size_t offset;
    if (!str_find(str, it->delimiter, &offset))
    {
        offset = str.length;
    }

    *out_token = str_sub(str, 0, offset);

    size_t new_start = min(offset + it->delimiter.length, str.length);
    it->str = str_sub(str, new_start, str.length);

    return true;
}

bool str_parse_int(str_t str, int* out_result)
{
    *out_result = 0;

    if (str.length == 0) return false;

    bool negative = *str.data == '-';
    if (negative)
    {
        str = str_sub(str, 1, str.length);
        if (!str.length) return false;
    }

    for (const char* c = str_begin(str); c != str_end(str); c = str_next(c))
    {
        if (*c < '0' || *c > '9') return false;

        *out_result = *out_result * 10 + (*c - '0');
    }

    if (negative) *out_result = -(*out_result);
    return true;
}