// Prompt two integers and swap them via another function.

#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a, b;

    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);

    swap(&a, &b);

    printf("\nSwapped!\n\n");

    printf("a = %d\nb = %d\n", a, b);

    return 0;
}
