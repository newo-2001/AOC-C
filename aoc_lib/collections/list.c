#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "../math.h"

ListOptions list_default_options()
{
    return (ListOptions) {
        .grow_factor = 2.0f,
        .initial_capacity = 8,
    };
}

List list_create_with_options(size_t item_size, ListOptions options)
{
    return (List) {
        .capacity = options.initial_capacity,
        .size = 0,
        .grow_factor = options.grow_factor,
        .item_size = item_size,
        .data = malloc(item_size * options.initial_capacity),
    };
}

void list_destroy(List list)
{
    free(list.data);
}

void list_reserve_exact(List* list, size_t num_items)
{
    void* old_data = list->data;

    list->capacity = num_items;
    list->data = malloc(list->item_size * num_items);
    memcpy(list->data, old_data, list->item_size * min(list->size, num_items));

    free(old_data);
}

void list_reserve(List* list, size_t num_items)
{
    size_t min_size = list->size + num_items;
    if (list->capacity >= min_size) return;

    float exponent = ceilf(nlogf((float) min_size, list->grow_factor));
    size_t new_size = (size_t) powf(list->grow_factor, exponent);
    list_reserve_exact(list, new_size);
}

void* list_get(List list, size_t index)
{
    assert(index < list.size);

    return ((char*) list.data) + index * list.item_size;
}

void list_append(List* list, slice_t items)
{
    assert(list->item_size == items.item_size);

    list_reserve(list, items.length);

    void* end = ((char*) list->data) + list->size * list->item_size;
    memcpy(end, items.data, items.length * list->item_size);

    list->size += items.length;
}

void list_push(List* list, void* item)
{
    slice_t array = (slice_t) {
        .item_size = list->item_size,
        .length = 1,
        .data = item,
    };

    list_append(list, array);
}

slice_t list_as_slice(List list)
{
    return (slice_t) {
        .item_size = list.item_size,
        .length = list.size,
        .data = list.data,
    };
}
