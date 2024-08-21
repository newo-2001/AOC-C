#include "hash.h"
#include "../vendor/md5.h"

int hash_djb2(void* data, size_t size)
{
    int hash = 5381;
    for (size_t i = 0; i < size; i++)
    {
        unsigned char byte = ((uint8_t *) data)[i];
        hash = (hash << 5) + hash + byte;
    }

    return hash;
}

void hash_md5(void* data, size_t size, uint8_t* result)
{
    MD5Context ctx;
    md5Init(&ctx);
    md5Update(&ctx, (uint8_t *) data, strlen(data));
    md5Finalize(&ctx);

    memcpy(result, ctx.digest, 16);
}