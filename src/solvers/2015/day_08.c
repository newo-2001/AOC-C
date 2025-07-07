#include "../solvers.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int deflated_size(const char* escaped_str)
{
    int size = 0;

    while (*escaped_str)
    {
        if (*(escaped_str++) == '\\' && *(escaped_str++) == 'x')
        {
            escaped_str += 2;
        }
        
        size++;
    }

    return size - 2;
}

SolverResult solve_2015_day_08_part_1(const char* _input)
{
    char* input = strdup(_input);
    const char* line = strtok(input, "\n");
    int code_overhead = 0;

    while (line)
    {
        code_overhead += strlen(line) - deflated_size(line);
        line = strtok(NULL, "\n");
    }

    free(input);

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = code_overhead
    };
}