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

#ifdef SKIP_SLOW_SOLVERS
#define SLOW_SOLVER(solver) NULL
#else
#define SLOW_SOLVER(solver) solver
#endif

SolverResult solve_2015_day_01_part_1(const char* input);
SolverResult solve_2015_day_01_part_2(const char* input);
SolverResult solve_2015_day_02_part_1(const char* input);
SolverResult solve_2015_day_02_part_2(const char* input);
SolverResult solve_2015_day_03_part_1(const char* input);
SolverResult solve_2015_day_03_part_2(const char* input);
SolverResult solve_2015_day_04_part_1(const char* input);
SolverResult solve_2015_day_04_part_2(const char* input);
SolverResult solve_2015_day_05_part_1(const char* input);
SolverResult solve_2015_day_05_part_2(const char* input);
SolverResult solve_2015_day_06_part_1(const char* input);
SolverResult solve_2015_day_06_part_2(const char* input);

#endif