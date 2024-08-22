#include "hashmap.h"
#include "../../constants.h"
#include "../hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static bool keys_eq(HashMap map, const void* left, const void* right)
{
    if (left && right)
    {
        return !memcmp(left, right, map.key_size);
    }
    else return !(left || right);
}

HashMap hashmap_new(size_t key_size, size_t value_size, size_t buckets)
{
    return (HashMap) {
        .size = 0,
        .bucket_count = buckets,
        .key_size = key_size,
        .value_size = value_size,
        .buckets = calloc(buckets, sizeof(HashMapNode*))
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
    size_t index = hash_djb2(key, map->key_size) % map->bucket_count;
    HashMapNode** prev = &map->buckets[index];
    HashMapNode* node = *prev;

    while (node)
    {
        if (keys_eq(*map, node->key, key))
        {
            memcpy(node->value, value, map->value_size);
            return;
        }

        prev = &node->next;
        node = node->next;
    }

    *prev = (HashMapNode*) malloc(sizeof(HashMapNode));
    node = *prev;

    *node = (HashMapNode) {
        .key = malloc(sizeof(map->key_size)),
        .value = malloc(sizeof(map->value_size)),
        .next = NULL
    };

    memcpy(node->key, key, map->key_size);
    memcpy(node->value, value, map->value_size);

    map->size++;
}

void* hashmap_get(HashMap map, const void* key)
{
    size_t index = hash_djb2(key, map.key_size) % map.bucket_count;
    HashMapNode* node = map.buckets[index];

    while (node)
    {
        if (keys_eq(map, node->key, key)) return node->value;

        node = node->next;
    }

    return NULL;
}

static void print_bytes(const void* bytes, size_t amount)
{
    if (!bytes)
    {
        printf("NULL");
        return;
    }

    printf("{");
    for (size_t i = 0; i < amount; i++)
    {
        printf(" %02X", ((unsigned char*) bytes)[i]);
    }
    printf(" }");
}

void hashmap_debug(HashMap map)
{
    size_t size = hashmap_size(map);
    printf("HashMap[%d] {\n", (int) size);

    for (size_t bucket = 0; bucket < map.bucket_count; bucket++)
    {
        HashMapNode* node = map.buckets[bucket];
        if (node) printf("  [%d] =", (int) bucket);
        else continue;

        while (node)
        {
            printf(" (");
            print_bytes(node->key, map.key_size);
            printf(": ");
            print_bytes(node->value, map.value_size);
            printf(") ->");

            node = node->next;
        }

        printf("\n");
    }

    printf("}\n");
}