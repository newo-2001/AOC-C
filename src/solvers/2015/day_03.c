#include "../solvers.h"
#include "../../lib/geometry.h"
#include "../../lib/collections/hashset.h"

static inline Direction parse_direction(char direction)
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

SolverResult solve_2015_day_03_part_1(char* input)
{
    Vec2 position = { 0, 0 };
    HashSet visited = hashset_new(sizeof(Vec2), 1000);

    char c;
    while ((c = *(input++)))
    {
        hashset_insert(&visited, &position);

        Direction direction = parse_direction(c);
        position = vec2_addv(position, dir_unit_vec(direction));
    }

    SolverResult result;
    result.type = RESULT_INT;
    result.integer_result = (int) hashset_size(visited);
    hashset_destroy(visited);

    return result;
}

SolverResult solve_2015_day_03_part_2(char* input)
{
    HashSet visited = hashset_new(sizeof(Vec2), 1000);
    Vec2 santa_pos = { 0, 0 };
    Vec2 robo_santa_pos = { 0, 0 };

    char c;
    while ((c = *(input++)))
    {
        hashset_insert(&visited, &santa_pos);
        hashset_insert(&visited, &robo_santa_pos);

        santa_pos = vec2_addv(santa_pos, dir_unit_vec(parse_direction(c)));
        
        if (!(c = *(input++))) break;
        robo_santa_pos = vec2_addv(robo_santa_pos, dir_unit_vec(parse_direction(c)));
    }

    SolverResult result = {
        .type = RESULT_INT,
        .integer_result = (int) hashset_size(visited)
    };

    hashset_destroy(visited);
    return result;
}