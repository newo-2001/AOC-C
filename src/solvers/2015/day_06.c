#include "../solvers.h"
#include "../../lib/geometry.h"
#include "../../lib/strutils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

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

static Instruction parse_instruction(const char* str)
{
    Instruction result;

    const char* remaining;
    if ((remaining = skip_str(str, "toggle"))) result.type = INST_TOGGLE;
    else if ((remaining = skip_str(str, "turn on"))) result.type = INST_ENABLE;
    else if ((remaining = skip_str(str, "turn off"))) result.type = INST_DISABLE;

    sscanf(
        remaining + 1,
        "%i,%i through %i,%i",
        &result.area.top_left.x,
        &result.area.top_left.y,
        &result.area.bottom_right.x,
        &result.area.bottom_right.y
    );

    return result;
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

static int sum_lights(uint32_t* grid) {
    int count = 0;
    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        count += grid[i];
    }

    return count;
}

static SolverResult solve(const char* _input, Instruction (*instruction_set)(Instruction))
{
    SolverResult result;
    result.type = RESULT_INT;

    char* input = strdup(_input);
    strtok(input, "\n");

    uint32_t* grid = calloc(GRID_SIZE, sizeof(uint32_t));

    do
    {
        Instruction instruction = instruction_set(parse_instruction(input));
        execute_instruction(instruction, grid);
    } while ((input = strtok(NULL, "\n")));

    result.integer_result = sum_lights(grid);

    free(grid);
    free(input);
    return result;
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

SolverResult solve_2015_day_06_part_1(const char* input) { return solve(input, digital); }
SolverResult solve_2015_day_06_part_2(const char* input) { return solve(input, analog); }