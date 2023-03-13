#include <stdio.h>
#define MAXLINE 1000
/* Reads the line from input and returns the line len in bytes */
int getline(char *p) {
    char *end = p + MAXLINE;
    int c;
    while((c = getchar()) != EOF && p < end - 1 && c != '\n')
        *p++ = c;
    if(c == '\n')
        *p++ = '\n';
    *p = '\0';
    return (int) (p - (end - MAXLINE));
}