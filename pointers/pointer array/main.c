#include <stdio.h>
#include "parray.h"
#define MAXLINES 1000

char *lineptr[MAXLINES];

int main() {
    int lines, i;

    lines = readlines(lineptr, MAXLINES);
    if(lines == -1) {
        printf("Error: Can't read any more lines, too much input!\n");
        return 1;
    }

    quicksort(lineptr, 0, lines-1);
    printarray(lineptr, lines);
    return 0;
}

