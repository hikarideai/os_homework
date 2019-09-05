// Implementation of an in-place bubble sort.
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int array[], int size);

// Test case
int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage:\n%s [int1 [int2 [...]]]", argv[0]);
        return 0;
    }

    int *array = (int *)malloc((argc - 1) * sizeof(int));
    for (int i = 0; i < argc - 1; ++i) {
        if (sscanf(argv[i + 1], "%d", &array[i]) == EOF) {
            printf("error: The argument %d is not an integer.\n", i + 1);
            free(array);
            return 0;
        }
    }

    printf("original: ");
    for (int i = 0; i < argc - 1; ++i)
        printf("%d ", array[i]);
    printf("\n");

    bubble_sort(array, argc - 1);

    printf("sorted:   ");
    for (int i = 0; i < argc - 1; ++i)
        printf("%d ", array[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int _a[], int _s) {
    for (int i = 0; i < _s; ++i) {
        for (int j = i + 1; j < _s; ++j) {
            if (_a[i] > _a[j]) {
                int temp = _a[i];
                _a[i] = _a[j];
                _a[j] = temp;
            }
        }
    }
}
