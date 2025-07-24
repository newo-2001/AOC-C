#ifndef AOC_HASHMAP_H
#define AOC_HASHMAP_H

#include <stddef.h>
#include <stdbool.h>

#include "../hash.h"

typedef void HashMapDebugFormatter(const void *data, size_t size);
typedef bool HashMapKeyComparer(const void *a, const void *b, size_t key_size);

typedef struct HashMapNode
{
    void *key;
    void *value;
    struct HashMapNode *next;
} HashMapNode;

typedef struct HashMap
{
    size_t size;
    size_t key_size;
    size_t value_size;

    size_t bucket_count;
    HashMapNode **buckets;

    HashMapKeyComparer *key_comparer;
    HashFunction *hash_function;
} HashMap;

typedef struct HashMapOptions
{
    size_t bucket_count;

    HashMapKeyComparer *key_comparer;
    HashFunction *hash_function;
} HashMapOptions;

HashMapOptions hashmap_default_options();
HashMap hashmap_new(size_t key_size, size_t value_size, HashMapOptions options);

void hashmap_destroy(HashMap map);

void hashmap_insert(HashMap *map, const void *key, const void *value);
void *hashmap_get(HashMap map, const void *key);

void hashmap_dbg(HashMap map, HashMapDebugFormatter key_formatter, HashMapDebugFormatter value_formatter);
void hashmap_dbg_fmt_hex(const void *data, size_t size);
void hashmap_dbg_fmt_str(const void *data, size_t size);

bool hashmap_str_eq(const void *a, const void *b, size_t key_size);
int hashmap_str_hash(const void *data, size_t size);

static inline bool hashmap_contains_key(HashMap map, const void *key)
{
    return hashmap_get(map, key) != NULL;
}

static inline size_t hashmap_size(HashMap map)
{
    return map.size;
}

#endif