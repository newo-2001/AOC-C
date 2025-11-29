#include "hashmap.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../hash.h"
#include "../str.h"

static bool mem_eq(const void* a, const void* b, size_t key_size)
{
    if (a && b)
    {
        return !memcmp(a, b, key_size);
    }

    return !(a || b);
}

static inline size_t bucket_for_key(HashMap map, const void* key)
{
    return map.hash_function(key, map.key_size) % map.bucket_count;
}

/// @brief Finds the `HashMapNode` for a given key.
/// @param map The map to find the node in.
/// @param key The key that identifies the node.
/// @param out_ref An optional out parameter for the location
/// that stores the link to the found node.
/// @return The node with the given key, or `NULL` if it is not found.
static inline HashMapNode* find_node_for_key(HashMap map, const void* key, HashMapNode*** out_ref)
{
    size_t bucket_index = bucket_for_key(map, key);
    HashMapNode** ref = &map.buckets[bucket_index];
    HashMapNode* node = *ref;

    while (node)
    {
        if (map.key_comparer(key, node->entry.key, map.key_size))
        {
            break;
        }

        ref = &node->next;
        node = *ref;
    }

    if (out_ref)
    {
        *out_ref = ref;
    }

    return node;
}

HashMapOptions hashmap_default_options()
{
    return (HashMapOptions) {
        .bucket_count = 1000,
        .key_comparer = mem_eq,
        .hash_function = hash_djb2,
    };
}

HashMap hashmap_create_with_options(size_t key_size, size_t value_size, HashMapOptions options)
{
    return (HashMap) {
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
            HashMapNode* next = node->next;
            free(node->entry.key);
            free(node);
            node = next;
        }
    }

    free(map.buckets);
}

void hashmap_insert(HashMap* map, const void* key, const void* value)
{
    HashMapNode** ref;
    HashMapNode* node = find_node_for_key(*map, key, &ref);

    if (!node)
    {
        *ref = malloc(sizeof(HashMapNode));
        node = *ref;

        char* data = malloc(map->key_size + map->value_size);
        *node = (HashMapNode) {
            .entry = (HashMapEntry) {
                .key = data,
                .value = data + map->key_size,
            },
            .next = NULL,
        };

        map->size++;
    }

    memcpy(node->entry.key, key, map->key_size);
    memcpy(node->entry.value, value, map->value_size);
}

bool hashmap_remove(HashMap* map, const void* key)
{
    HashMapNode** ref;
    HashMapNode* node = find_node_for_key(*map, key, &ref);

    if (!node) return false;

    *ref = node->next;
    free(node->entry.key);
    free(node);
    map->size--;

    return true;
}

void* hashmap_get(HashMap map, const void* key)
{
    HashMapNode* node = find_node_for_key(map, key, NULL);
    return node ? node->entry.value : NULL;
}

HashMapIter hashmap_iter(HashMap map)
{
    return (HashMapIter) {
        .map = map,
        .bucket_index = 0,
        .node = NULL,
    };
}

HashMapEntry* hashmap_iter_next(HashMapIter* iter)
{
    if (!iter->node)
    {
        iter->node = iter->map.buckets[0];
        if (iter->node)
        {
            return &iter->node->entry;
        }
    }
    else if (iter->node->next)
    {
        iter->node = iter->node->next;
        return &iter->node->entry;
    }

    do
    {
        if (++iter->bucket_index >= iter->map.bucket_count)
        {
            return NULL;
        }

        iter->node = iter->map.buckets[iter->bucket_index];
    } while (!iter->node);

    return &iter->node->entry;
}

void hashmap_dbg(HashMap map, HashMapDebugFormatter key_formatter, HashMapDebugFormatter value_formatter)
{
    printf("HashMap[%d] {\n", (int) map.size);

    for (size_t bucket = 0; bucket < map.bucket_count; bucket++)
    {
        HashMapNode* node = map.buckets[bucket];
        if (node == NULL) continue;

        printf("  [%d] =", (int) bucket);

        while (node)
        {
            fputs(" (", stdout);
            key_formatter(node->entry.key, map.key_size);
            fputs(": ", stdout);
            value_formatter(node->entry.value, map.value_size);
            fputs(") ->", stdout);

            node = node->next;
        }

        puts("");
    }

    puts("}\n");
}

bool hashmap_eq_str(const void* a, const void* b, size_t key_size)
{
    (void) key_size;

    str_t a_str = *((str_t*) a);
    str_t b_str = *((str_t*) b);

    return !str_cmp(a_str, b_str);
}

int hashmap_hash_str(const void* data, size_t size)
{
    (void) size;

    str_t str = *((str_t*) data);
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
        printf(" %02X", ((uint8_t*) data)[i]);
    }
    fputs(" }", stdout);
}

void hashmap_dbg_fmt_str(const void* data, size_t size)
{
    (void) size;

    str_t str = *((str_t*) data);
    printf("%.*s", (int) str.length, str.data);
}