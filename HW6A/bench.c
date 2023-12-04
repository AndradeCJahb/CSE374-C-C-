/* bench.c is the benchmarking /test program for mem memory management
   bench.c is implemented as part of HW6, CSE374 22WI
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "mem.h"


/* print_stats is a helper function that prints performance
   information about the memory system.  Requires a clock_t start
   time, and prints elapsed time plus results from get_mem_stats()
*/
void print_stats(clock_t start);

/* fill_mem is a helper function that takes in an address and the
   size of the memory allocation at that address.  It should fill
   the first 16 bytes (or up to size) with hexedecimal values.*/
void fill_mem(void* ptr, uintptr_t size);

/* Synopsis:  bench (main)
   [ntrials] (10000) getmem + freemem calls
   [pctget] (50) % of calls that are get mem
   [pctlarge] (10) % of calls requesting more memory than lower limit
   [small_limit] (200) largest size in bytes of small block
   [large_limit] (20000) largest size in byes of large block
   [random_seed] (time) initial seed for rand
*/
int main(int argc, char** argv ) {
    int ntrials = 10000;
    int pctget = 50;
    int pctlarge = 10;
    int small_limit = 200;
    int large_limit = 20000;
    int random_seed = (int)time(NULL);

    if (argc > 1) ntrials = atoi(argv[1]);
    if (argc > 2) pctget = atoi(argv[2]);
    if (argc > 3) pctlarge = atoi(argv[3]);
    if (argc > 4) small_limit = atoi(argv[4]);
    if (argc > 5) large_limit = atoi(argv[5]);
    if (argc > 6) random_seed = atoi(argv[6]);

    srand(random_seed);


    void* blocks[ntrials];
    int nblocks = 0;
    clock_t start = clock();

    for (int i = 0; i < ntrials; i++) {
        if ((rand() % 100) < pctget) {
            uintptr_t size;
            if ((rand() % 100) < pctlarge) {
                size = small_limit + (rand() % (large_limit - small_limit+ 1));
            } else {
                size = 1 + (rand() % small_limit);
            }

            blocks[nblocks] = getmem(size);
            if (blocks[nblocks] != NULL) {
                fill_mem(blocks[nblocks], size);

                nblocks++;
            }
        } else {
            if (nblocks > 0) {
                int idx = rand() % nblocks;
                freemem(blocks[idx]);
                blocks[idx] = blocks[nblocks - 1];

                nblocks--;
            }
        }

        if (i % (ntrials / 10) == 0 && i > 10) {
            print_stats(start);
        }
    }

    print_stats(start);
    return EXIT_SUCCESS;
}

void print_stats(clock_t start) {
    clock_t end = clock();
    double elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    uintptr_t total_size, total_free, n_free_blocks;
    get_mem_stats(&total_size, &total_free, &n_free_blocks);

    double avg_bytes = (double) total_free / n_free_blocks;

    printf("Elapsed Time: %.6f seconds | Total Size: %lu bytes | "
           "Total Free Blocks: %lu | Avg Bytes: %.2f\n",
           elapsed_time, total_size, n_free_blocks, avg_bytes);
}

void fill_mem(void* ptr, uintptr_t size) {
    uintptr_t bytes_to_fill = (size < 16) ? size : 16;

    for (uintptr_t i = 0; i < bytes_to_fill; i++) {
        ((unsigned char*)ptr)[i] = 0xFE;
    }
}
