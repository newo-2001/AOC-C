#ifndef AOC_SLICE_H
#define AOC_SLICE_H

#include <stddef.h>
#include <stdbool.h>

/// @brief A slice is a contiguous block of data of a fixed size.
/// This structure does not own the underlying data, it merely provides a view into it.
typedef struct slice_t
{
    size_t item_size;
    size_t length;
    void* data;
} slice_t;

#define STACK_SLICE(type, items)                                                                                       \
    ((slice_t) {                                                                                                       \
        .item_size = sizeof(type),                                                                                     \
        .length = sizeof(items) / sizeof(type),                                                                        \
        .data = &items[0],                                                                                             \
    })

/// @brief Creates an iterator over a `slice`.
inline static void* slice_start(slice_t slice)
{
    return slice.data;
}

/// @brief Advances the given iterator.
inline static void* slice_next(slice_t slice, void* it)
{
    return ((char*) it) + slice.item_size;
}

/// @brief Returns a pointer beyond the last element in `slice`.
inline static void* slice_end(slice_t slice)
{
    return ((char*) slice.data) + slice.item_size * slice.length;
}

#endif