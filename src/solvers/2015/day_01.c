#include <string.h>
#include <stdlib.h>
#include "../solvers.h"

SolverResult solve_2015_day_01_part_1(const char* input) {
    SolverResult result;
    int floor = 1;

    char c;
    while ((c = *(input++)))
    {
        if (c == '(') floor++;
        else if (c == ')') floor--;
    }

    result.type = RESULT_INT;
    result.integer_result = floor;
    return result;
}

SolverResult solve_2015_day_01_part_2(const char* input) {
    SolverResult result;
    const char* input_start = input;
    int floor = 0;

    char c;
    while((c = *(input++)))
    {
        if (c == '(') floor++;
        else if (c == ')') floor--;

        if (floor < 0)
        {
            result.type = RESULT_INT;
            result.integer_result = input - input_start;
            return result;
        }
    }

    result.type = RESULT_STATIC_ERR;
    result.string_result = "Santa did not enter the basement";
    return result;
}