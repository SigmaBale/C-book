#include <stdio.h>
#include "parray.h"
#define MAXLINE 1000

static void strcopy(char *src, char *dst)
{
    while (*src++ = *dst++)
        ;
}

static size_t strlength(char *str)
{
    register const char *s;
    for (s = str; *s != '\0'; ++s)
        ;
    return (s - str);
}

/* Reads the line from input and returns the line len in bytes */
int getline(char *p)
{
    char *end = p + MAXLINE;
    int c;

    while (p < end - 1 && (c = getchar()) != EOF && c != '\n')
    {
        *p++ = c;
    }

    if (c == '\n')
        *p++ = '\n';

    *p = '\0';

    return (int)(p - (end - MAXLINE));
}

int readlines(char *array[], int lines, char *ap)
{
    int i, len;
    char *p, line[MAXLINE];

    p = ap + strlength(ap);
    for (i = 0; (len = getline(line)) > 0; i++)
    {
        if (i >= lines || (strlength(p) + len) > MAXSIZE)
            return -1;
        line[len - 1] = '\0';
        strcopy(p, line);
        array[i] = p;
        p += len;
    }
    return i;
}

void printarray(char *a[], int len)
{
    int i;
    for (i = 0; i < len; i++)
        printf("%s\n", a[i]);
    return;
}