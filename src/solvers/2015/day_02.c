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

static bool parse_present(str_t line, Present* out_present)
{
    str_t num;
    int* side = (int*)&out_present->length;
    StrSpliterator it = str_split(line, SLICE("x"));

    while (str_split_next(&it, &num))
    {
        if (!str_parse_int(num, side++)) return false;
    }

    return true;
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

static SolverResult solve(str_t input, uint32_t (*measure)(Present))
{
    uint32_t total_wrapping_paper = 0;

    str_t line;
    StrSpliterator it = str_lines(input);
    while (str_split_next(&it, &line))
    {
        Present present;
        if (!parse_present(line, &present))
        {
            return (SolverResult){
                .type = RESULT_STATIC_ERR,
                .value.string = "Failed to parse present",
            };
        }

        total_wrapping_paper += measure(present);
    }

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = total_wrapping_paper,
    };
}

SolverResult solve_2015_day_02_part_1(str_t input) { return solve(input, wrapping_paper); }
SolverResult solve_2015_day_02_part_2(str_t input) { return solve(input, ribbon); }