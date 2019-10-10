#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    char* p;
    for (int i = 0; i < 10; i++) {
        p = malloc(1 << 20);
        memset(p, 0, 1 << 20);
        sleep(1);
    }
    return 0;
}
