// Print sizes and max values of some of the basic C types.

#include <limits.h>
#include <float.h>
#include <stdio.h>

int main() {
    int a = INT_MAX;
    float b = FLT_MAX;
    double c = DBL_MAX;

    printf("Type\tSize\tValue\n");
    printf("INT\t%zd\t%d\n", sizeof a, a);
    printf("FLOAT\t%zd\t%f\n", sizeof b, b);
    printf("DOUBLE\t%zd\t%f\n", sizeof c, c);

    return 0;
}
