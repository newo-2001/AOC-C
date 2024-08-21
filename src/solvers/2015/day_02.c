#include "../solvers.h"
#include "../../lib/strutils.h"
#include <string.h>
#include <stdio.h>
#include <minmax.h>

typedef struct Present
{
    int length;
    int width;
    int height;
} Present;

static Present parse_present(const char* str)
{
    Present present;
    sscanf(str, "%ix%ix%i", &present.length, &present.width, &present.height);
    return present;
}

static inline int wrapping_paper(Present present)
{
    int front = present.height * present.width;
    int side = present.height * present.length;
    int top = present.width * present.length;
    int slack = min(min(front, side), top);

    return 2 * (front + side + top) + slack;
}

static inline int ribbon(Present present)
{
    int bow = present.width * present.height * present.length;
    int front = present.height + present.width;
    int side = present.height + present.length;
    int top = present.width + present.length;

    return 2 * min(min(front, side), top) + bow;
}

SolverResult solve_2015_day_02_part_1(const char* input)
{
    SolverResult result;
    result.type = RESULT_INT;
    result.integer_result = 0;

    do
    {
        result.integer_result += wrapping_paper(parse_present(input));
    } while ((input = strchr(input, '\n') + 1) != (const char*) 1);

    return result;
}

SolverResult solve_2015_day_02_part_2(const char* input)
{
    SolverResult result;
    result.type = RESULT_INT;
    result.integer_result = 0;

    do
    {
        result.integer_result += ribbon(parse_present(input));
    } while ((input = strchr(input, '\n') + 1) != (const char*) 1);

    return result;
}