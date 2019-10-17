#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// How many page frames are available to the user
#define PFRM_COUNT 100

// How many page references occur in a single clock tick
#define CLOCK_INT 1

// How much bits are used to store age
#define MEM_FRAME 64

typedef struct {
    int i;
    uint64_t age;
} page_t;

int main() {
    page_t pmap[PFRM_COUNT];
    unsigned char rbit[PFRM_COUNT];
    memset(pmap, 0, sizeof(pmap));
    memset(rbit, 0, sizeof(rbit));

    FILE* file = fopen("input.xt", "r");
    if (file == NULL) {
        printf("Could't open the input file\n");
        return 1;
    }

    int page_req, page_cnt = 0;
    int hits = 0, misses = 0;

    while (!feof(file)) {
        fscanf(file, "%d", &page_req);
        if (feof(file))
            break;

        if (page_cnt % CLOCK_INT == 0) {
            for (int i = 0; i < PFRM_COUNT; ++i) {
                pmap[i].age = ((uint64_t)(rbit[i] & 1) << (MEM_FRAME - 1)) | (pmap[i].age >> 1);
                rbit[i] = 0;
            }
        }
        page_cnt++;

        int x = -1, oldest = 0;
        for (int i = 0; i < PFRM_COUNT; ++i) {
            if (pmap[i].i == page_req)
                x = i;
            if (pmap[i].age < pmap[oldest].age)
                oldest = i;
        }

        if (x != -1) {
            hits++;
            rbit[x] = 1;
            continue;
        }

        misses++;
        pmap[oldest].i = page_req;
        pmap[oldest].age = 0;
        rbit[oldest] = 1;
    }

    printf("Hits\tMisses\n%d\t%d\n", hits, misses);
    return 0;
}
