#include "../solvers.h"
#include "../../lib/geometry.h"
#include "../../lib/collections/hashmap.h"

static inline Direction parse_direction(Direction direction)
{
    switch (direction)
    {
        case '^': return DIR_NORTH;
        case '>': return DIR_EAST;
        case 'v': return DIR_SOUTH;
        case '<': return DIR_WEST;
        default: return -1;
    }
}

SolverResult solve_2015_day_03_part_1(const char* input)
{
    Vec2 position = { 0, 0 };
    HashMap visited = hashmap_new(sizeof(Vec2), 0, 1000);

    char c;
    while ((c = *(input++)))
    {
        hashmap_insert(visited, &position, NULL);

        Direction direction = parse_direction(c);
        position = vec2_addv(position, dir_unit_vec(direction));
    }

    SolverResult result;
    result.type = RESULT_INT;
    result.integer_result = hashmap_size(visited);
    hashmap_destroy(visited);

    return result;
}

SolverResult solve_2015_day_03_part_2(const char* input)
{
    HashMap visited = hashmap_new(sizeof(Vec2), 0, 1000);
    Vec2 santa_pos = { 0, 0 };
    Vec2 robo_santa_pos = { 0, 0 };

    char c;
    while ((c = *(input++)))
    {
        hashmap_insert(visited, &santa_pos, NULL);
        hashmap_insert(visited, &robo_santa_pos, NULL);

        santa_pos = vec2_addv(santa_pos, dir_unit_vec(parse_direction(c)));
        
        if (!(c = *(input++))) break;
        robo_santa_pos = vec2_addv(robo_santa_pos, dir_unit_vec(parse_direction(c)));
    }

    SolverResult result;
    result.type = RESULT_INT;
    result.integer_result = hashmap_size(visited);
    hashmap_destroy(visited);

    return result;
}