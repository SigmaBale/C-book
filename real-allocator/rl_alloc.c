#include "rl_alloc.h"
#include <stdbool.h>
#include <unistd.h>

/// Internal function for expanding the process data segment.
static sk_chunkptr _sk_morecore(size_t chunks);

/// Allocator chunk that acts as header by storing
/// the allocation size and as alignment for allocated memory.
/// Stores the pointer to the next chunk, because it
/// acts as a node in the singly-linked list.
struct sk_chunk {
    sk_chunkptr next;
    size_t      size;
};

/// Turn bytes into number of chunks required to make that
/// allocation.
#define into_chunks(bytes) (bytes + sizeof(sk_chunk) - 1) / sizeof(sk_chunk) + 1

/// Initialize the singly-linked list by initializing
/// the first chunk.
static sk_chunk    first_chunk = { .next = &first_chunk, .size = 0 };
/// Initialize the globalptr, it points to the last
/// allocated chunk.
static sk_chunkptr globalptr = NULL;

/// Allocates 'BYTES' bytes on the heap returning the
/// pointer to the start of the allocation.
void*
sk_alloc_mem(size_t bytes)
{
    sk_chunkptr current = NULL;
    sk_chunkptr prev    = globalptr;

    /// Turn the number of bytes requested into chunks
    size_t chunks = into_chunks(bytes);

    /// If globalptr is NULL that can only mean that free-list
    /// is empty and this is the first memory allocation.
    if(globalptr == NULL) {
        /// Set the pointers to point to the static chunk.
        /// Meaning free-list is an actual circular singly-linked list.
        globalptr = &first_chunk;
        current   = &first_chunk;
        prev      = &first_chunk;
    }

    bool allocating = true;

    current = prev->next;
    /// Let's traverse the singly linked list in order to
    /// find the chunk with fitting size.
    while(allocating) {
        /// If we found the big enough chunk lets fix the
        /// free list so the previous chunk (globalptr) and
        /// current chunk size are valid
        if(current->size >= chunks) {
            /// If current chunk size is exactly the same size
            /// as required then just unlink the whole chunk from
            /// the free list by setting the previous chunks next pointer
            /// to point to the current chunks next chunk.
            if(current->size == chunks) {
                globalptr->next = current->next;
            } else {
                /// If the current chunk size is bigger we will
                /// move the current chunk forward until the
                /// chunk starting address + 'chunks' equal to the
                /// end address of the chunk.
                /// We will return tail of the current chunk.
                current->size -= chunks;
                current       += current->size;
                current->size = chunks;
            }

            /// globalptr will point to the chunk that was
            /// just before the returned chunk.
            globalptr = prev;
            /// Lets exit the loop, we are done allocating
            allocating = false;
        }

        /// If we traversed all the list chunks and wrapped around but still
        /// didn't find the fitting allocation, then lets actually allocate
        if(current == globalptr) {
            /// Request the memory from OS and return
            /// the chunk just before the allocated chunk,
            /// that way we will fetch the next chunk in the
            /// next iteration, and return the allocation to the callee.
            if((current = _sk_morecore(chunks)) == NULL) {
                return NULL;
            }
        }

        /// Iterate through the list, fetch next chunk.
        current = current->next;
        /// Cache previous chunk because we are singly linked
        /// list, so we can set the globalptr to prev when
        /// returning the chunk.
        prev = current;
    }

    /// Return start of the allocation which starts
    /// after the first 'sk_chunk' (header).
    return current + 1;
}

/// self explanatory...
#define MIN_CHUNKS_ALLOCATED 1024

/// Internal function for raising 'program break' aka
/// expanding the heap memory, returns the pointer to the allocation
/// or NULL if chunks is zero and/or heap can't be expanded.
sk_chunkptr
_sk_morecore(size_t chunks)
{
    if(chunks == 0) {
        return NULL;
    }

    /// Make sure we are allocating at least
    /// minimal amount of chunks specified
    /// for performance sake
    if(chunks < MIN_CHUNKS_ALLOCATED) {
        chunks = MIN_CHUNKS_ALLOCATED;
    }

    void*       new_chunks = NULL;
    sk_chunkptr chunk      = NULL;

    /// If we can't raise the 'program break' return NULL
    if((new_chunks = sbrk(chunks * sizeof(sk_chunk))) == (void*) -1) {
        return NULL;
    }

    /// Get the first chunk (header) from the new_chunks
    /// and set its size to the amount of 'chunks'.
    chunk       = (sk_chunk*) new_chunks;
    chunk->size = chunks;

    /// Actual requested allocation is all the memory
    /// beyond the first chunk (header) up to the 'chunks' size.
    void* allocation = new_chunks + 1;

    /// Insert the new allocation into our free-list.
    sk_free(allocation);

    /// Returning globalptr set by 'sk_free' to point
    /// right before the insertion in the linked list
    return globalptr;
}

void
sk_free(void* allocation)
{
    /// Get the header chunk that is one chunk (at least 'word' size)
    /// behind the start of the allocation
    sk_chunk* chunkp = (sk_chunk*) allocation - 1;

    /// Iteration pointer
    sk_chunk* current;

    /// Traverse the free-list to find the 'hole' where we will
    /// insert the chunk, if chunk address is bigger than the current chunk
    /// and smaller than the next chunk in the list then we found the 'hole'.
    for(current = globalptr; !(chunkp > current && chunkp < current->next); current = current->next)
    {
        /// There are few edge cases where the current chunk is either at the end
        /// of the free-list and the 'next' chunk would be the start of the list
        /// (smallest memory address of the arena) or the current chunk is the
        /// only chunk in the free-list (address of the next is same).
        if(current >= current->next && (chunkp > current || chunkp < current->next)) {
            break;
        }
    }

    /// If this is not the first edge case where the current chunk
    /// was at the end of the list, then combine the freed chunk
    /// and the 'next' chunk together.
    if(chunkp + chunkp->size == current->next) {
        chunkp->size += current->next->size;
        chunkp->next = current->next->next;
    } else {
        /// We hit the first edge case where the 'current' was
        /// at the end of the list, we can't combine because
        /// 'current->next' is pointing at the start of the free-list.
        chunkp->next = current->next;
    }

    /// If the freed chunk memory address comes right after the
    /// current chunk then combine them together.
    if(current + current->size == chunkp) {
        current->size += chunkp->size;
        current->next = chunkp->next;
    } else {
        /// Current chunk is at the end of the free-list
        /// therefore the freed chunk was inserted at the
        /// start of the free-list, we can't combine them
        current->next = chunkp;
    }

    /// Set globalptr to point just before the insertion
    /// in the list, this way if we were allocating, then
    /// in the next iteration we will find the fitting chunk
    /// Also other reason is there is a high chance we combined
    /// multiple chunks together, and this might immediatly satisfy
    /// the next 'sk_alloc_mem' call.
    globalptr = current;
}
