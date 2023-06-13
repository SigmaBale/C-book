#include <stddef.h>

typedef struct sk_chunk sk_chunk;

typedef sk_chunk *sk_chunkptr;

void *sk_alloc(size_t bytes);
void sk_free(void *allocation);
void *sk_calloc(size_t n, size_t size);
