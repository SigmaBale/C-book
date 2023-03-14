#include <stdio.h>
#include "parray.h"
#define MAXLINE 1000

static void strcopy(char *src, char *dst) {
    while(*src++ = *dst++)
        ;
}

/* Reads the line from input and returns the line len in bytes */
int getline(char *p) {
    char *end = p + MAXLINE;
    int c;

    while(p < end - 1 && (c = getchar()) != EOF && c != '\n') {
        *p++ = c;
    }

    if(c == '\n')
        *p++ = '\n';

    *p = '\0';

    return (int) (p - (end - MAXLINE));
}

int readlines(char *array[], int lines) {
    int i, len;
    char *p, line[MAXLINE];

    for(i = 0; (len = getline(line)) > 0; i++) {
        if(i >= lines || (p = alloc(len)) == NULL)
            return -1;
        line[len-1] = '\0';
        strcopy(p, line);
        array[i] = p;
    }
    return i;
}

void printarray(char *a[], int len) {
    int i;
    for(i = 0; i < len; i++)
        printf("%s\n", a[i]);
    return;
}