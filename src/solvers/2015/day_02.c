#include "../solvers.h"
#include <string.h>
#include <stdio.h>
#include <minmax.h>

typedef struct Present
{
    unsigned int length;
    unsigned int width;
    unsigned int height;
} Present;

static Present parse_present(const char* str)
{
    Present present;
    sscanf(str, "%ux%ux%u", &present.length, &present.width, &present.height);
    return present;
}

static inline unsigned int wrapping_paper(Present present)
{
    unsigned int front = present.height * present.width;
    unsigned int side = present.height * present.length;
    unsigned int top = present.width * present.length;
    unsigned int slack = min(min(front, side), top);

    return 2 * (front + side + top) + slack;
}

static inline unsigned int ribbon(Present present)
{
    unsigned int bow = present.width * present.height * present.length;
    unsigned int front = present.height + present.width;
    unsigned int side = present.height + present.length;
    unsigned int top = present.width + present.length;

    return 2 * min(min(front, side), top) + bow;
}

SolverResult solve_2015_day_02_part_1(char* input)
{
    unsigned int total_wrapping_paper = 0;

    strtok(input, "\n");

    do
    {
        total_wrapping_paper += wrapping_paper(parse_present(input));
    } while ((input = strtok(NULL, "\n")));

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = (int) total_wrapping_paper
    };
}

SolverResult solve_2015_day_02_part_2(char* input)
{
    unsigned int total_ribbon = 0;

    strtok(input, "\n");

    do
    {
        total_ribbon += ribbon(parse_present(input));
    } while ((input = strtok(NULL, "\n")));

    return (SolverResult) {
        .type = RESULT_INT,
        .integer_result = (int) total_ribbon
    };
}