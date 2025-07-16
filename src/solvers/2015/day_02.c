#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <aoc_lib/math.h>

#include "../solvers.h"

typedef struct Present
{
    uint32_t length;
    uint32_t width;
    uint32_t height;
} Present;

static Present parse_present(const char* str)
{
    Present present;
    sscanf(str, "%ux%ux%u", &present.length, &present.width, &present.height);
    return present;
}

static unsigned int wrapping_paper(Present present)
{
    uint32_t front = present.height * present.width;
    uint32_t side = present.height * present.length;
    uint32_t top = present.width * present.length;
    uint32_t slack = min(min(front, side), top);

    return 2 * (front + side + top) + slack;
}

static uint32_t ribbon(Present present)
{
    uint32_t bow = present.width * present.height * present.length;
    uint32_t front = present.height + present.width;
    uint32_t side = present.height + present.length;
    uint32_t top = present.width + present.length;

    return 2 * min(min(front, side), top) + bow;
}

SolverResult solve_2015_day_02_part_1(const char* _input)
{
    uint32_t total_wrapping_paper = 0;

    char* input = strdup(_input);
    const char* line = strtok(input, "\n");

    while (line)
    {
        total_wrapping_paper += wrapping_paper(parse_present(line));
        line = strtok(NULL, "\n");
    }

    free(input);

    return (SolverResult) {
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = total_wrapping_paper
    };
}

SolverResult solve_2015_day_02_part_2(const char* _input)
{
    unsigned int total_ribbon = 0;

    char* input = strdup(_input);
    char* line = strtok(input, "\n");

    while (line)
    {
        total_ribbon += ribbon(parse_present(line));
        line = strtok(NULL, "\n");
    }

    free(input);

    return (SolverResult) {
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = total_ribbon
    };
}