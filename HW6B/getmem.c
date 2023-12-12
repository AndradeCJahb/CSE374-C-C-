/* getmem.c
   implements getmem (malloc) for memory system
   CSE 374 HW6
*/

#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include "mem.h"
#include "mem_impl.h"
#include <stdio.h>

/* initialize global variables ?*/
freeNode* free_list = NULL;
uintptr_t totalmalloc = 0;
/* Are there helper functions that only getmem will need?  Declare here. */

void split_node(freeNode* n, uintptr_t size);

void* getmem(uintptr_t size) {
  /* make sure you return a pointer to the usable memory that
     is at least 'size' bytes long.
     To get you started we are 'stubbing in' a call that will
     return a usable value.  You will replace this code. */

    // Ensure that size is positive
    if (size < 1) {
        return NULL;
    }

    uintptr_t totalSize = size + NODESIZE;

    // Calculate the total size including the header and align it to 16 bytes
    if (totalSize % 16 != 0) {
        totalSize = totalSize - totalSize % 16 + 16;
    }

    freeNode* current = free_list;
    freeNode* prev = NULL;

    while (current != NULL && current->size < totalSize) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        int newSize = BIGCHUNK;
        if(BIGCHUNK < totalSize)
        {
            newSize = totalSize;
        }
        current = (freeNode*)malloc(newSize);
        if (current == NULL)
        {
            return NULL;
        }
        current->size = newSize - NODESIZE;
        split_node(current, totalSize);
    } else {
        if(current->size > totalSize + MINCHUNK + NODESIZE) {
            split_node(current, totalSize);
        }
    }

    if (prev == NULL) {
        free_list = current;
    } else {
        prev->next = current;
    }

    totalmalloc = totalmalloc + totalSize;

    return ((void*)current + NODESIZE);
}

void split_node(freeNode* n, uintptr_t totalSize) {
    freeNode* newNode = (freeNode*)((uintptr_t)(n) + totalSize);
    newNode->size = n->size - totalSize;
    newNode->next = n->next;
    n->size = totalSize - NODESIZE;
    n->next = newNode;
}