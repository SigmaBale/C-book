#include <stdio.h>
#include <string.h>
#include "tail.h"
#define MAXLINE 1000

size_t gline(char *p, int size) {
    int c;
    char *start = p;

    while(--size > 0 && (c = getchar()) != EOF && c != '\n')
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = '\0';
    return (size_t) (p - start);
}

int write_lines(char *buf[], int *bufp) {
    int len;
    char *ptr, line[MAXLINE];

    while((len = gline(line, MAXLINE)) > 0) {
        if((ptr = alloc(len)) == NULL)
            return 1;
        line[len-1] = '\0';
        strcpy(ptr, line);
        buf[(*bufp)++] = ptr;
    }
    return 0;
}
