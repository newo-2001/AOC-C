#ifndef AOC_HASHSET_H
#define AOC_HASHSET_H

#include "hashmap.h"

typedef struct HashSet
{
    HashMap map;
} HashSet;

inline static HashSet hashset_new(size_t item_size, size_t buckets)
{
    return (HashSet) { hashmap_new(item_size, 0, buckets) };
}

inline static void hashset_destroy(HashSet set)
{
    hashmap_destroy(set.map);
}

inline static size_t hashset_size(HashSet set)
{
    return hashmap_size(set.map);
}

inline static void hashset_insert(HashSet* set, const void* item)
{
    hashmap_insert(&set->map, item, NULL);
}

inline static bool hashset_contains(HashSet set, const void* item)
{
    return hashmap_contains_key(set.map, item);
}

#endif
