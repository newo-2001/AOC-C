#include "hash.h"

int hash_djb2(const void* data, size_t size)
{
    int hash = 5381;
    for (size_t i = 0; i < size; i++)
    {
        unsigned char byte = ((uint8_t *) data)[i];
        hash = (hash << 5) + hash + byte;
    }

    return hash;
}