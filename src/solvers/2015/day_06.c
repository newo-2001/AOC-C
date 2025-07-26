#include "../solvers.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <aoc_lib/geometry.h>
#include <aoc_lib/strutils.h>

typedef enum InstructionType
{
    INST_DISABLE,
    INST_ENABLE,
    INST_TOGGLE,
    INST_INC,
    INST_DEC,
    INST_INC2
} InstructionType;

typedef struct Area
{
    Vec2 top_left;
    Vec2 bottom_right;
} Area;

typedef struct Instruction
{
    InstructionType type;
    Area area;
} Instruction;

static bool parse_pos(str_t str, Vec2* out_result)
{
    StrSpliterator comma = str_split(str, SLICE(","));

    return str_split_next(&comma, &str) && str_parse_int(str, &out_result->x) && str_split_next(&comma, &str) &&
           str_parse_int(str, &out_result->y);
}

static bool parse_instruction(str_t str, Instruction* out_result)
{
    if (str_contains(str, SLICE("toggle"))) out_result->type = INST_TOGGLE;
    else if (str_contains(str, SLICE("turn on"))) out_result->type = INST_ENABLE;
    else if (str_contains(str, SLICE("turn off"))) out_result->type = INST_DISABLE;

    size_t sep_pos;
    str_t sep = SLICE(" through ");

    return str_find(str, sep, &sep_pos) && parse_pos(str_sub(str, 0, sep_pos), &out_result->area.top_left) &&
           parse_pos(str_sub(str, sep_pos + sep.length, str.length), &out_result->area.bottom_right);
}

#define GRID_WIDTH 1000
#define GRID_HEIGHT 1000
#define GRID_SIZE (GRID_WIDTH * GRID_HEIGHT)

static void execute_instruction(Instruction instruction, uint32_t* grid)
{
    for (int y = instruction.area.top_left.y; y <= instruction.area.bottom_right.y; y++)
    {
        for (int x = instruction.area.top_left.x; x <= instruction.area.bottom_right.x; x++)
        {
            uint32_t* cell = grid + y * GRID_WIDTH + x;

            switch (instruction.type)
            {
                case INST_ENABLE:
                    *cell = true;
                    break;
                case INST_DISABLE:
                    *cell = false;
                    break;
                case INST_TOGGLE:
                    *cell = !*cell;
                    break;
                case INST_INC:
                    (*cell)++;
                    break;
                case INST_DEC:
                    *cell = *cell == 0 ? 0 : *cell - 1;
                    break;
                case INST_INC2:
                    (*cell) += 2;
                    break;
            }
        }
    }
}

static int sum_lights(uint32_t* grid)
{
    int count = 0;
    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        count += grid[i];
    }

    return count;
}

static SolverResult solve(str_t input, Instruction (*instruction_set)(Instruction))
{
    uint32_t* grid = calloc(GRID_SIZE, sizeof(uint32_t));

    str_t line;
    StrSpliterator it = str_lines(input);
    while (str_split_next(&it, &line))
    {
        Instruction inst;
        if (!parse_instruction(line, &inst))
        {
            return (SolverResult){
                .type = RESULT_STATIC_ERR,
                .value.string = "Failed to parse instruction",
            };
        }
        execute_instruction(instruction_set(inst), grid);
    }

    uint32_t lights = sum_lights(grid);

    free(grid);

    return (SolverResult){
        .type = RESULT_UNSIGNED_INT,
        .value.unsigned_int = lights,
    };
}

static Instruction digital(Instruction instruction) { return instruction; }

static Instruction analog(Instruction instruction)
{
    switch (instruction.type)
    {
        case INST_ENABLE:
            instruction.type = INST_INC;
            break;
        case INST_DISABLE:
            instruction.type = INST_DEC;
            break;
        case INST_TOGGLE:
            instruction.type = INST_INC2;
            break;
        default:
            assert(false);
    }

    return instruction;
}

SolverResult solve_2015_day_06_part_1(str_t input) { return solve(input, digital); }
SolverResult solve_2015_day_06_part_2(str_t input) { return solve(input, analog); }