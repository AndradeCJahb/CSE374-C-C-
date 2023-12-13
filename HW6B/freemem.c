/* freemem.c
   implements freemem (free) for memory system
   CSE 374 HW6
*/

#include <stdlib.h>
#include <assert.h>
#include "mem.h"
#include "mem_impl.h"

/* This code will be filled in by the students.  Your primary job is to
   implement freemem functions.  */

/* initialize global variables? */

/* Are there helper functions that only freemem needs?  Declare here. */

/* Define your functions below: */


void combine();

void freemem(void* p) {
    if (p == NULL) {
        return;
    }

    freeNode* chunk = (freeNode*)((uintptr_t)p - NODESIZE);
    uintptr_t chunkSize = chunk->size;

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

    totalmalloc = totalmalloc - chunkSize - NODESIZE;

    combine();
}

void combine()
{
    freeNode* current = freelist;
    while (current != NULL && current->next != NULL) {
        if ((uintptr_t)current + NODESIZE + current->size == (uintptr_t)current->next) {
            // Combine the current block with the next one
            current->size = current->size + NODESIZE + current->next->size;
            current->next = current->next->next;
        } else {
            // Move to the next block
            current = current->next;
        }
    }
}

