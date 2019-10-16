#include <stdio.h>
#include <string.h>

// How many page frames are available to the user
#define PFRM_COUNT 100

// How many page references occur in a single clock tick
#define CLOCK_INT 100

struct page {
    int i;
    int age;
};
typedef struct page page_t;

int main() {
    page_t pmap[PFRM_COUNT];
    char rbit[PFRM_COUNT];
    memset(pmap, 0, sizeof(pmap));
    memset(rbit, 0, sizeof(rbit));

    FILE* file = fopen("Lab 09 input.txt", "r");
    if (file == NULL) {
        printf("Could't open the input file\n");
        return 1;
    }

    int page_req, page_cnt = 0;
    int hits = 0, misses = 0;

    while (!feof(file)) {
        fscanf(file, "%d", &page_req);
        if (page_cnt % CLOCK_INT == 0) {
            for (int i = 0; i < PFRM_COUNT; ++i)
                pmap[i].age = ((rbit[i] & 1) << 31) | (pmap[i].age >> 1);
        }
        page_cnt++;

        int x = -1, oldest = 0;
        for (int i = 0; i < PFRM_COUNT; ++i) {
            if (pmap[i].i == page_req)
                x = i;
            if (pmap[i].age > pmap[oldest].age)
                oldest = i;
        }

        if (x != -1) {
            hits++;
            continue;
        }

        misses++;
        pmap[oldest].i = page_req;
        pmap[oldest].age = (1 << 31);
    }

    printf("Hits\tMisses\n%d\t%d\n", hits, misses);
    return 0;
}
