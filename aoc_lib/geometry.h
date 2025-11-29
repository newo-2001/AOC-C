#ifndef AOC_GEOMETRY_H
#define AOC_GEOMETRY_H

typedef struct Vec2 {
    int x;
    int y;
} Vec2;

static inline Vec2 vec2_addv(Vec2 left, Vec2 right)
{
    return (Vec2) { .x = left.x + right.x, .y = left.y + right.y };
}

typedef enum Direction {
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST
} Direction;

Vec2 dir_unit_vec(Direction direction);

#endif