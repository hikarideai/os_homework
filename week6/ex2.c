// EX2 -- An example where pipe() is used to transfer data between processes.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pp[2];

    if (pipe(pp) < 0)
        exit(1);

    char astr[] = "I lliw deeccus";
    char bstr[sizeof(astr)];

    if (fork() == 0) {
        if (write(pp[1], astr, sizeof(astr)) < 0) {
            fprintf(stderr, "Failed to write to the pipe.\n");
            exit(1);
        }

        wait(NULL);
    } else {
        read(pp[0], bstr, sizeof(astr));
        printf("Read \"%s\" from the pipe.\n", bstr);
    }

    return 0;
}
