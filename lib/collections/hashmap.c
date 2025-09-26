#include "hashmap.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../hash.h"
#include "../slice.h"

static bool keys_eq(const void* a, const void* b, size_t key_size)
{
    if (a && b)
    {
        return !memcmp(a, b, key_size);
    }

    return !(a || b);
}

HashMapOptions hashmap_default_options()
{
    return (HashMapOptions){
        .bucket_count = 1000,
        .key_comparer = keys_eq,
        .hash_function = hash_djb2,
    };
}

HashMap hashmap_new(size_t key_size, size_t value_size, HashMapOptions options)
{
    return (HashMap){
        .size = 0,
        .bucket_count = options.bucket_count,
        .key_size = key_size,
        .value_size = value_size,
        .key_comparer = options.key_comparer,
        .hash_function = options.hash_function,
        .buckets = calloc(options.bucket_count, sizeof(HashMapNode*)),
    };
}

void hashmap_destroy(HashMap map)
{
    for (size_t bucket = 0; bucket < map.bucket_count; bucket++)
    {
        HashMapNode* node = map.buckets[bucket];

        while (node)
        {
            free(node->key);
            free(node->value);

            HashMapNode* prev = node;
            node = prev->next;
            free(prev);
        }
    }

    free(map.buckets);
}

void hashmap_insert(HashMap* map, const void* key, const void* value)
{
    size_t index = map->hash_function(key, map->key_size) % map->bucket_count;
    HashMapNode** prev = &map->buckets[index];
    HashMapNode* node = *prev;

    while (node)
    {
        if (map->key_comparer(node->key, key, map->key_size))
        {
            memcpy(node->value, value, map->value_size);
            return;
        }

        prev = &node->next;
        node = node->next;
    }

    *prev = malloc(sizeof(HashMapNode));
    node = *prev;

    *node = (HashMapNode){.key = malloc(map->key_size), .value = malloc(map->value_size), .next = NULL};

    memcpy(node->key, key, map->key_size);
    memcpy(node->value, value, map->value_size);

    map->size++;
}

void* hashmap_get(HashMap map, const void* key)
{
    size_t index = map.hash_function(key, map.key_size) % map.bucket_count;
    HashMapNode* node = map.buckets[index];

    while (node)
    {
        if (map.key_comparer(node->key, key, map.key_size))
        {
            return node->value;
        }

        node = node->next;
    }

    return NULL;
}

void hashmap_dbg(HashMap map, HashMapDebugFormatter key_formatter, HashMapDebugFormatter value_formatter)
{
    printf("HashMap[%d] {\n", (int)map.size);

    for (size_t bucket = 0; bucket < map.bucket_count; bucket++)
    {
        HashMapNode* node = map.buckets[bucket];
        if (node) printf("  [%d] =", (int)bucket);
        else continue;

        while (node)
        {
            fputs(" (", stdout);
            key_formatter(node->key, map.key_size);
            fputs(": ", stdout);
            value_formatter(node->value, map.value_size);
            fputs(") ->", stdout);

            node = node->next;
        }

        puts("");
    }

    puts("}\n");
}

bool hashmap_eq_str(const void* a, const void* b, size_t key_size)
{
    (void)key_size;

    str_t a_str = *((str_t*)a);
    str_t b_str = *((str_t*)b);

    return !str_cmp(a_str, b_str);
}

int hashmap_hash_str(const void* data, size_t size)
{
    (void)size;

    str_t str = *((str_t*)data);
    return hash_djb2(str.data, str.length);
}

void hashmap_dbg_fmt_hex(const void* data, size_t size)
{
    if (!data)
    {
        fputs("NULL", stdout);
        return;
    }

    fputs("{", stdout);
    for (size_t i = 0; i < size; i++)
    {
        printf(" %02X", ((uint8_t*)data)[i]);
    }
    fputs(" }", stdout);
}

void hashmap_dbg_fmt_str(const void* data, size_t size)
{
    (void)size;

    str_t str = *((str_t*)data);
    printf("%.*s", (int)str.length, str.data);
}