#ifndef AOC_LIST_H
#define AOC_LIST_H

#include <stddef.h>

/// @brief A dynamic array that grows as new items are pushed into it.
/// The list may re-allocate the backing array at any point;
/// when this happens, the `data` pointer is invalidated.
typedef struct List
{
    size_t size;
    size_t capacity;
    float grow_factor;

    size_t item_size;
    void* data;
} List;

typedef struct ListOptions
{
    size_t initial_capacity;
    float grow_factor;
} ListOptions;

ListOptions list_default_options();

List list_new_options(size_t, ListOptions options);
inline static List list_new(size_t item_size) { return list_new_options(item_size, list_default_options()); }

void list_destroy(List list);

/// @brief Reserves space for at least `num_items` additional items.
/// This can be used to prevent excessive allocations.
/// Note: The function might not re-allocate if there is already enough space.
/// @param list The list to operate on.
/// @param num_items The number of additional items to reserve space for.
void list_reserve(List* list, size_t num_items);

/// @brief Reserves space for exactly `num_items`.
/// This function will also shrink the list to match this size if it is bigger.
/// This can be used to prevent excessive allocations.
/// @param list The list to operate on.
/// @param num_items The number of items to reserve space for.
void list_reserve_exact(List* list, size_t num_items);

#endif