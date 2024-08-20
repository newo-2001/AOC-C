#ifndef AOC_SOLVERS_H
#define AOC_SOLVERS_H

typedef enum SolverResultType
{
    RESULT_ERR,
    RESULT_STATIC_ERR,
    RESULT_INT,
    RESULT_STRING,
    RESULT_STATIC_STRING
} SolverResultType;

typedef struct SolverResult
{
    SolverResultType type;
    union {
        char* string_result;
        int integer_result;
    };
} SolverResult;

typedef SolverResult (*Solver)(const char* input);

SolverResult solve_2015_day_01_part_1(const char* input);
SolverResult solve_2015_day_01_part_2(const char* input);
SolverResult solve_2015_day_02_part_1(const char* input);
SolverResult solve_2015_day_02_part_2(const char* input);
SolverResult solve_2015_day_03_part_1(const char* input);
SolverResult solve_2015_day_03_part_2(const char* input);

#endif