#include "../solvers.h"

SolverResult solve_2015_day_01_part_1(str_t input)
{
    SolverResult result;
    int32_t floor = 0;

    for (const char* c = str_begin(input); c != str_end(input); c++)
    {
        if (*c == '(') floor++;
        else if (*c == ')') floor--;
    }

    result.type = RESULT_SIGNED_INT, result.value.signed_int = floor;
    return result;
}

SolverResult solve_2015_day_01_part_2(str_t input)
{
    int32_t floor = 0;

    for (const char* c = str_begin(input); c != str_end(input); c++)
    {
        if (*c == '(') floor++;
        else if (*c == ')') floor--;

        if (floor < 0)
        {
            return (SolverResult){
                .type = RESULT_UNSIGNED_INT,
                .value.unsigned_int = c - str_begin(input) + 1,
            };
        }
    }

    return (SolverResult){
        .type = RESULT_STATIC_ERR,
        .value.string = "Santa did not enter the basement",
    };
}