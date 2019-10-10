#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    char* p;
    for (int i = 0; i < 10; i++) {
        p = malloc(1 << 20);
        memset(p, 0, 1 << 20);
        struct rusage usg;
        getrusage(RUSAGE_SELF, &usg);
        printf("MEM: %ldKB\n", usg.ru_maxrss);
        sleep(1);
    }
    return 0;
}
