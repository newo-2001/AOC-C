#include "geometry.h"

Vec2 dir_unit_vec(Direction direction)
{
    switch (direction)
    {
        case DIR_NORTH: return (Vec2) { 0, -1 };
        case DIR_EAST: return (Vec2) { 1, 0 };
        case DIR_SOUTH: return (Vec2) { 0, 1 };
        case DIR_WEST: return (Vec2) { -1, 0 };
        default: return (Vec2) { 0, 0 };
    }
}