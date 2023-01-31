#include <stdio.h>
#include "quicksort.h"

#define SIZE 12

int main()
{
    int i;
    int list[SIZE] = { 1, 5, 8, 15, 3, 12, 8, 2, 4, 33, 6, 151 };

    for(i = 0; i < SIZE; i++)
        printf("[%d]", list[i]);
    printf("\n");

    quicksort(list, 0, SIZE-1);

    for(i = 0; i < SIZE; i++)
        printf("[%d]", list[i]);
    printf("\n");

    return 0;
}