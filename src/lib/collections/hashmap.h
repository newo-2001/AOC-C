#ifndef AOC_HASHMAP_H
#define AOC_HASHMAP_H

#include "stddef.h"
#include "../../constants.h"

typedef struct HashMapNode
{
    void* key;
    void* value;
    struct HashMapNode* next;
} HashMapNode;

typedef struct HashMap
{
    size_t bucket_count;
    size_t key_size;
    size_t value_size;
    size_t size;
    HashMapNode** buckets;
} HashMap;

HashMap hashmap_new(size_t key_size, size_t value_size, size_t buckets);
void hashmap_destroy(HashMap map);
void hashmap_insert(HashMap* map, const void* key, const void* value);
void* hashmap_get(HashMap map, const void* key);
void hashmap_debug(HashMap map);

static inline bool hashmap_contains_key(HashMap map, const void* key)
{
    return hashmap_get(map, key) != NULL;
}

static inline size_t hashmap_size(HashMap map)
{
    return map.size;
}

#endif