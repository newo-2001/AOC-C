#include "../solvers.h"
#include "../../lib/geometry.h"
#include "../../lib/strutils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum InstructionType
{
    INST_DISABLE,
    INST_ENABLE,
    INST_TOGGLE
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

static void execute_instruction(Instruction instruction, uint8_t* grid)
{
    for (int y = instruction.area.top_left.y; y <= instruction.area.bottom_right.y; y++)
    {
        uint8_t* row_start = grid + y * GRID_WIDTH;

        if (instruction.type == INST_TOGGLE)
        {
            for (int x = instruction.area.top_left.x; x <= instruction.area.bottom_right.x; x++)
            {
                uint8_t* cell = row_start + x;
                *cell = !*cell;
            }
        }
        else
        {
            size_t size = instruction.area.bottom_right.x - instruction.area.top_left.x + 1;
            memset(row_start + instruction.area.top_left.x, (bool) instruction.type, size);
        }
    }
}

static int count_lights(uint8_t* grid) {
    int count = 0;
    for (size_t i = 0; i < GRID_SIZE; i++)
    {
        count += grid[i] == true;
    }

    return count;
}

SolverResult solve_2015_day_06_part_1(const char* _input)
{
    SolverResult result;
    result.type = RESULT_INT;

    char* input = strdup(_input);
    strtok(input, "\n");

    uint8_t* grid = calloc(GRID_SIZE, sizeof(uint8_t));

    do
    {
        Instruction instruction = parse_instruction(input);
        execute_instruction(instruction, grid);
    } while ((input = strtok(NULL, "\n")));

    result.integer_result = count_lights(grid);

    free(grid);
    free(input);
    return result;
}