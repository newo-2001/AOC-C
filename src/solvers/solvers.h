#ifndef AOC_SOLVERS_H
#define AOC_SOLVERS_H

#include <stdint.h>

#include <aoc_lib/str.h>

typedef enum SolverResultType
{
    RESULT_DYNAMIC_ERR,
    RESULT_STATIC_ERR,
    RESULT_DYNAMIC_STRING,
    RESULT_STATIC_STRING,
    RESULT_UNSIGNED_INT,
    RESULT_SIGNED_INT
} SolverResultType;

typedef struct SolverResult
{
    SolverResultType type;
    union
    {
        char* string;
        int64_t signed_int;
        uint64_t unsigned_int;
    } value;
} SolverResult;

typedef SolverResult (*Solver)(str_t input);

#ifdef SKIP_SLOW_SOLVERS
#define SLOW_SOLVER(solver) NULL
#else
#define SLOW_SOLVER(solver) solver
#endif

#define SOLVERS_PART(year, day, part) SolverResult solve_##year##_day_##day##_part_##part(str_t input);

#define SOLVERS_DAY(year, day)                                                                                         \
    SOLVERS_PART(year, day, 1)                                                                                         \
    SOLVERS_PART(year, day, 2)

SOLVERS_DAY(2015, 01)
SOLVERS_DAY(2015, 02)
SOLVERS_DAY(2015, 03)
SOLVERS_DAY(2015, 04)
SOLVERS_DAY(2015, 05)
SOLVERS_DAY(2015, 06)
SOLVERS_DAY(2015, 07)
SOLVERS_DAY(2015, 08)

SOLVERS_DAY(2025, 01)

#undef SOLVE_DAY
#undef SOLVE_PART

#endif