#include <stddef.h>
#include <stdint.h>

typedef struct sk_chunk sk_chunk;

typedef sk_chunk *sk_chunkptr;

void *sk_alloc_mem(size_t bytes);
void sk_free(void *allocation);
