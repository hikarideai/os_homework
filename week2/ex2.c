// Prompt a string and print its reverse.

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 5000

int main() {
    printf("Please, enter a string: ");
    
    char buf[BUF_SIZE];
    fgets(buf, BUF_SIZE, stdin);

    size_t len = strlen(buf);
    for (size_t i = 0; i < len / 2; ++i) {
        char temp = buf[i];
        buf[i] = buf[len - i - 1];
        buf[len - i - 1] = temp;
    }

    // Since fgets doesn't get rid of the \n at the end of the string
    // We should do it ourselves.
    char *str = buf[0] == '\n' ? buf + 1 : buf;
    printf("%s\n", str);

    return 0;
}
