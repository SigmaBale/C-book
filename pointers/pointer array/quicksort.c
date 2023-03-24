#include <stdio.h>

static int strcmp(char *a, char *b)
{
    for (; *a == *b; a++, b++)
        if (*a == '\0')
            return 0;
    return *a - *b;
}

static void swap(char *a[], int src, int dst)
{
    char *temp;
    temp = a[src];
    a[src] = a[dst];
    a[dst] = temp;
}

static int partition(char *a[], int start, int end)
{
    int pivot, pivot_id, id;

    pivot = end;
    pivot_id = start;

    for (id = pivot_id; id <= pivot - 1; id++)
        if (strcmp(a[id], a[pivot]) < 0)
            swap(a, id, pivot_id++);

    swap(a, pivot, pivot_id);
    return pivot;
}

void quicksort(char *a[], int start, int end)
{
    if (start < end)
    {
        int pivot = partition(a, start, end);
        quicksort(a, start, pivot - 1);
        quicksort(a, pivot + 1, end);
    }
    return;
}