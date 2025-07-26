#include "list.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../math.h"

ListOptions list_default_options()
{
    return (ListOptions){
        .grow_factor = 2.0f,
        .initial_capacity = 8,
    };
}

List list_new_options(size_t item_size, ListOptions options)
{
    return (List){
        .capacity = options.initial_capacity,
        .size = 0,
        .grow_factor = options.grow_factor,
        .item_size = item_size,
        .data = malloc(item_size * options.initial_capacity),
    };
}

void list_destroy(List list) { free(list.data); }

void list_reserve_exact(List* list, size_t num_items)
{
    void* old_data = list->data;

    list->capacity = num_items;
    list->data = malloc(list->item_size * num_items);
    memcpy(list->data, old_data, list->item_size * list->size);

    free(old_data);
}

void list_reserve(List* list, size_t num_items)
{
    size_t min_size = list->size + num_items;
    if (list->capacity >= min_size) return;

    float exponent = ceilf(nlogf(min_size, list->grow_factor));
    size_t new_size = (size_t)powf(list->grow_factor, exponent);
    list_reserve_exact(list, new_size);
}