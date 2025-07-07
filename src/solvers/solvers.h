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

#define SOLVERS_PART(year, day, part) \
    SolverResult solve_ ## year ## _day_ ## day ## _part_ ## part (const char* input);

#define SOLVERS_DAY(year, day) \
    SOLVERS_PART(year, day, 1) \
    SOLVERS_PART(year, day, 2)

SOLVERS_DAY(2015, 01)
SOLVERS_DAY(2015, 02)
SOLVERS_DAY(2015, 03)
SOLVERS_DAY(2015, 04)
SOLVERS_DAY(2015, 05)
SOLVERS_DAY(2015, 06)
SOLVERS_DAY(2015, 07)
SOLVERS_DAY(2015, 08)

#undef SOLVE_DAY
#undef SOLVE_PART

#endif