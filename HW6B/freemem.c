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

void combine();

void freemem(void* p) {
    check_heap();

    if (p == NULL) {
        return;
    }

    freeNode* chunk = (freeNode*)((uintptr_t)p - NODESIZE);
    uintptr_t chunkSize = chunk->size;
    totalmalloc = totalmalloc - chunkSize - NODESIZE;

    // Add the block to the free list and sort by memory address
    freeNode* current = freelist;
    freeNode* prev = NULL;

    while (current != NULL && current < chunk) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

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
    freeNode* current = freelist;
    while (current != NULL && current->next != NULL) {
        if ((uintptr_t)current + NODESIZE + current->size ==
            (uintptr_t)current->next) {
            // Combine the current block with the next one
            current->size = current->size + NODESIZE + current->next->size;
            current->next = current->next->next;
        } else {
            // Move to the next block
            current = current->next;
        }
    }
}

