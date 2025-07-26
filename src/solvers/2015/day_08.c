#include "../solvers.h"

static size_t deflated_size(str_t escaped_str)
{
    size_t size = escaped_str.length + 2;

    for (const char* c = str_begin(escaped_str); c != str_end(escaped_str); c = str_next(c))
    {
        if (*(c++) == '\\' && *(c++) == 'x')
        {
            c += 2;
        }

        size--;
    }

    return size;
}

static size_t escaped_size(str_t str)
{
    size_t size = 0;

    for (const char* c = str_begin(str); c != str_end(str); c = str_next(c))
    {
        if (*c == '\\' || *c == '"') size++;
        size++;
    }

    return size + 2 - str.length;
}

static SolverResult solve(str_t input, size_t (*measure)(str_t line))
{
    size_t result = 0;

    str_t line;
    StrSpliterator it = str_lines(input);
    while (str_split_next(&it, &line))
    {
        result += measure(line);
    }

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = result,
    };
}

SolverResult solve_2015_day_08_part_1(str_t input) { return solve(input, deflated_size); }
SolverResult solve_2015_day_08_part_2(str_t input) { return solve(input, escaped_size); }