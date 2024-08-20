#ifndef AOC_HASHMAP_H
#define AOC_HASHMAP_H

#include "stddef.h"

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
    HashMapNode** buckets;
} HashMap;

HashMap hashmap_new(size_t key_size, size_t value_size, size_t buckets);
void hashmap_destroy(HashMap map);
void hashmap_insert(HashMap map, void* key, void* value);
size_t hashmap_size(HashMap map);
void hashmap_debug(HashMap map);

#endif