#include "../solvers.h"

SolverResult solve_2015_day_01_part_1(const char* input) {
    SolverResult result;
    int32_t floor = 0;

    char c;
    while ((c = *(input++)))
    {
        if (c == '(') floor++;
        else if (c == ')') floor--;
    }

    result.type = RESULT_SIGNED_INT,
    result.value.signed_int = floor;
    return result;
}

SolverResult solve_2015_day_01_part_2(const char* input) {
    const char* input_start = input;
    int32_t floor = 0;

    char c;
    while((c = *(input++)))
    {
        if (c == '(') floor++;
        else if (c == ')') floor--;

        if (floor < 0)
        {
            return (SolverResult) {
                .type = RESULT_UNSIGNED_INT,
                .value.unsigned_int = input - input_start
            };
        }
    }

    return (SolverResult) {
        .type = RESULT_STATIC_ERR,
        .value.string = "Santa did not enter the basement"
    };
}