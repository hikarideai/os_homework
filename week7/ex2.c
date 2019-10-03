#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    printf("Enter N. ");
    scanf("%d", &n);

    int* a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        a[i] = i;

    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");

    free(a);

    return 0;
}
