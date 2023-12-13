
/*
  Christopher Andrade
  12/13/2023
  getmem.c
  getmem.c implements getmem (malloc) for memory system
  Copyright 2023 Christopher Andrade
*/
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "mem.h"
#include "mem_impl.h"
#include <stdio.h>

freeNode* freelist = NULL;
uintptr_t totalmalloc = 0;

// Splits given node into two pieces, in the case that the proposed memory
// chunk is large enough to fit the smallest memory chunk.
void split_node(freeNode* n, uintptr_t size);

// Allocates and returns a pointer to allocated memory. The size of the
// returned memory chunk will be the parameter 'size' rounded to its
// next multiple of 16.
void* getmem(uintptr_t size) {
    check_heap();

    // Ensure that size is positive.
    if (size < 1) {
        return NULL;
    }

    uintptr_t totalSize = size + NODESIZE;

    // Ensures the total size allocated is divisible by 16.
    if (totalSize % 16 != 0) {
        totalSize = totalSize - (totalSize % 16) + 16;
    }

    // Initializes pointers to iterate through freelist.
    freeNode* current = freelist;
    freeNode* prev = NULL;

    // loops through freelist until a big enough free chunk is found or until end
    // of freelist.
    while (current != NULL && current->size < totalSize) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        if (BIGCHUNK + NODESIZE < totalSize) {
            // Creates new chunk which is larger than default big chunk size.
            // Splitting of newly created chunk is done if needed.
            current = (freeNode*)malloc(totalSize);
            if (current == NULL) {
                return NULL;
            }

            current->size = totalSize - NODESIZE;
            current->next = NULL;
        } else {
            // Creates new chunk which is the size of big chunk. Splitting
            // of newly created chunk is done if needed.
            current = (freeNode*)malloc(BIGCHUNK + NODESIZE);
            if (current == NULL) {
                return NULL;
            }

            current->size = BIGCHUNK;
            if (current->size > totalSize + MINCHUNK + NODESIZE) {
                split_node(current, totalSize);
            }
            freelist = current->next;
        }
    } else {
        // If chunk of sufficient size is found then it is allocated. Splitting
        // of existing chunk is done if needed.
        if (current->size > totalSize + MINCHUNK + NODESIZE) {
            split_node(current, totalSize);
        }
        if (prev !=NULL) {
            prev->next = current->next;
        } else {
            freelist = current->next;
        }
    }

    // Updates totalmalloc statistic which is the total size of allocated
    // chunks of memory.
    totalmalloc = totalmalloc + totalSize;
    return ((void*)current + NODESIZE);
}

void split_node(freeNode* n, uintptr_t totalSize) {
    freeNode* newNode = (freeNode*)((uintptr_t)(n) + totalSize);

    // fields of new node "ahead" of original are updated appropriately
    newNode->size = n->size - totalSize;
    newNode->next = n->next;

    // fields of original node are updated appropriately
    n->size = totalSize - NODESIZE;
    n->next = newNode;
}