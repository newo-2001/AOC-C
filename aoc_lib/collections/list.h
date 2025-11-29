#ifndef AOC_LIST_H
#define AOC_LIST_H

#include <stddef.h>

#include "../slice.h"

/// @brief A dynamic array that grows as new items are pushed into it.
/// The list may re-allocate the backing array on any modifying operation.
/// When this happens, the `data` pointer is invalidated.
typedef struct List
{
    size_t size;
    size_t capacity;
    float grow_factor;

    size_t item_size;
    void* data;
} List;

/// @brief Options to specify how a list is to be created,
/// to be used with `list_create_with_options`.
/// @param initial_capacity The number of elements to initially allocate space for.
/// @param grow_factor The factor by which to grow the list if it becomes full.
typedef struct ListOptions
{
    size_t initial_capacity;
    float grow_factor;
} ListOptions;

/// @return The default options for `list_create`.
ListOptions list_default_options();

/// @brief Creates a new list with the specified options.
/// @param item_size The size of each element in the list.
/// @param options The options to use.
/// @return The newly created list.
List list_create_with_options(size_t item_size, ListOptions options);

/// @brief Creates a new list using the default options.
/// @param item_size The size of each element in the list.
/// @return The newly created list.
inline static List list_create(size_t item_size)
{
    return list_create_with_options(item_size, list_default_options());
}

/// @brief Destroys a list, freeing the underlying resources.
/// @param list The list to destroy.
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

/// @brief Retrieves an element from a list at a given index.
/// @param list The list to operate on.
/// @param index The index of the element to retrieve.
/// @note Retrieving an index beyond `list.size` is undefined.
/// @return The element at `index`
void* list_get(List list, size_t index);

/// @brief Copies all items from the given slice to the end of the list.
/// Growing by reallocating if needed.
/// @param list The list to operate on.
/// @param items The items to append to the end of the list.
void list_append(List* list, slice_t items);

/// @brief Pushes an item to the back of the given list.
/// Growing by reallocating if needed.
/// @param list The list to operate on.
/// @param elements The element to push back.
void list_push(List* list, void* item);

/// @brief Obtains a view of the list as a slice.
/// This view is *not* a copy, any change to the original list invalidates this view.
/// @param list The list to view as a slice.
/// @return The view of the list as slice.
slice_t list_as_slice(List list);

/// @brief Creates an iterator over a `list`.
inline static void* list_start(List list)
{
    return list.data;
}

/// @brief Advances the given iterator.
inline static void* list_next(List list, void* it)
{
    return ((char*) it) + list.item_size;
}

/// @brief Returns a pointer beyond the last element in `list`.
inline static void* list_end(List list)
{
    return ((char*) list.data) + list.item_size * list.size;
}

#endif