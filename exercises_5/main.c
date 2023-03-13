#include <stdio.h>
#include "getval.h"

#define SIZE 10

int main()
{
    int n;
    float array[SIZE];
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        printf("value parsed: %f\n", array[n]);
    for (n = 0; n < SIZE; n++)
        printf("Value at index array[%d] = %f\n", n, array[n]);
    return 0;
}