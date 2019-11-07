#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STR_SIZE 21

int main() {
    int fd = open("/dev/random", O_RDONLY);
    if (fd == -1)
        return 1;

    unsigned char* str = malloc(STR_SIZE);
    read(fd, str, STR_SIZE - 1);

    printf("%s\n", str);
    for (int i = 0; i < STR_SIZE; i++)
        printf("%d ", str[i]);

    free(str);
    close(fd);

    return 0;
}
