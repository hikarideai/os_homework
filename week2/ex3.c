// Print an up-right triangle of height n and width 2n-1.

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define FILL_CHAR '*'

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Output an up-right triangle of height n and width 2n-1.\n"
               "Usage: %s <height-of-the-triangle>\n", argv[0]);
        return 1;
    }

    int n;
    sscanf(argv[1], "%d", &n);

    if (n < 0) {
        printf("The height should be a non-negative integer.\n");
        return 1;
    } else if (n == 0) {
        printf("\n");
        return 0;
    }

    char *line = (char *)malloc(2 * n);
    memset(line, ' ', 2 * n - 1);
    line[2 * n - 1] = '\0';

    // Grow triangle from the center to the boundaries and output line-by-line.
    for (int i = n - 1; i < 2 * n - 1; ++i) {
        line[i] = line[2 * n - i - 2] = FILL_CHAR;
        printf("%s\n", line);
    }

    free(line);
    return 0;
}
