#include "../solvers.h"

#include <stdlib.h>
#include <string.h>

static size_t deflated_size(const char* escaped_str)
{
    size_t size = strlen(escaped_str) + 2;

    while (*escaped_str)
    {
        if (*(escaped_str++) == '\\' && *(escaped_str++) == 'x')
        {
            escaped_str += 2;
        }
        
        size--;
    }

    return size;
}

static size_t escaped_size(const char* string)
{
    const char* str = string;
    size_t size = 0;

    char c;
    while ((c = *(str++)))
    {
        if (c == '\\' || c == '"') size++;
        size++;
    }

    return size + 2 - strlen(string);
}

SolverResult solve(const char* _input, size_t (*measure)(const char*))
{
    char* input = strdup(_input);
    const char* line = strtok(input, "\n");
    size_t result = 0;

    while (line)
    {
        result += measure(line);
        line = strtok(NULL, "\n");
    }

    free(input);

    return (SolverResult) {
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = result
    };
}

SolverResult solve_2015_day_08_part_1(const char* input) { return solve(input, deflated_size); }
SolverResult solve_2015_day_08_part_2(const char* input) { return solve(input, escaped_size); }