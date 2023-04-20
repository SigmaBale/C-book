#include <stdio.h>
#include <string.h>
#include "parray.h"
char * alloc(unsigned int size);

static size_t gline(char *p, int size) {
    int c;
    char *start = p;

    while(--size > 0 && (c = getchar()) != EOF && c != '\n')
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = '\0';
    return (size_t) (p - start);
}

int readlines(char *array[], int maxlines) {
    int i, len;
    char *p, line[MAXLINE];

    for (i = 0; (len = gline(line, MAXLINE)) > 0; i++) {
        if (i >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len - 1] = '\0';
        strcpy(p, line);
        array[i] = p;
    }
    return i;
}

void printarray(char *a[], int len) {
    int i;
    for (i = 0; i < len; i++)
        printf("%s\n", a[i]);
    return;
}
