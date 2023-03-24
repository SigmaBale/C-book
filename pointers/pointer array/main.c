#include <stdio.h>
#include "parray.h"
#define MAXLINES 2000

char *lineptr[MAXLINES];

int main()
{
    int lines, i;
    char buff[MAXSIZE];

    lines = readlines(lineptr, MAXLINES, buff);
    if (lines == -1)
    {
        printf("Error: Can't read any more lines, too much input!\n");
        return 1;
    }
    quicksort(lineptr, 0, lines - 1);
    printarray(lineptr, lines);
    return 0;
}
