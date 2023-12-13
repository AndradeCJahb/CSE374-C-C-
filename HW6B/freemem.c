/*
  Christopher Andrade
  12/13/2023
  freemem.c
  freemem.c implements freemem (free) for memory system
  Copyright 2023 Christopher Andrade
*/
#include <stdlib.h>
#include <assert.h>
#include "mem.h"
#include "mem_impl.h"

// Combines adjacent free memory chunks
void combine();

// Returns the given memory chunk back to the freelist to classify it
// as a free memory chunk.
void freemem(void* p) {
    check_heap();

    if (p == NULL) {
        return;
    }

    freeNode* chunk = (freeNode*)((uintptr_t)p - NODESIZE);
    uintptr_t chunkSize = chunk->size;
    totalmalloc = totalmalloc - chunkSize - NODESIZE;

    // Initializes pointers required to loop through freelist.
    freeNode* current = freelist;
    freeNode* prev = NULL;

    // Iterates through freelist until arrived at address which is to be
    // freed, or end of freelist.
    while (current != NULL && current < chunk) {
        prev = current;
        current = current->next;
    }

    // Ensures no memory is freed if given address is not a chunk of memory
    // that hasn't been allocated.
    if (current == NULL) {
        return;
    }

    // Fixes pointers to add chunk of memory back into freelist.
    if (prev == NULL) {
        freelist = chunk;
    } else {
        prev->next = chunk;
    }

    chunk->next = current;
    chunk->size = chunkSize;

    combine();
}

void combine()
{
    // Loops through each node within freelist to ensure that there are no
    // two free memory chunks directly adjacent to one another.
    freeNode* current = freelist;
    while (current != NULL && current->next != NULL) {
        // Checks if address of next chunk is the same as the current chunk
        // address + its own size.
        if ((uintptr_t)current + NODESIZE + current->size ==
            (uintptr_t)current->next) {

            // Combine the current block with the next one
            current->size = current->size + NODESIZE + current->next->size;
            current->next = current->next->next;
        } else {
            current = current->next;
        }
    }
}

