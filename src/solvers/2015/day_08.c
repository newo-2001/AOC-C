#include "../solvers.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int deflated_size(const char* escaped_str)
{
    int size = strlen(escaped_str) + 2;

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

static int escaped_size(const char* str)
{
    int size = -strlen(str);

    char c;
    while ((c = *(str++)))
    {
        if (c == '\\' || c == '"') size++;
        size++;
    }

    return size + 2;
}

SolverResult solve(const char* _input, int (*measure)(const char*))
{
    char* input = strdup(_input);
    const char* line = strtok(input, "\n");
    int result = 0;

    while (line)
    {
        result += measure(line);
        line = strtok(NULL, "\n");
    }

    free(input);

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = result
    };
}

SolverResult solve_2015_day_08_part_1(const char* input) { return solve(input, deflated_size); }
SolverResult solve_2015_day_08_part_2(const char* input) { return solve(input, escaped_size); }