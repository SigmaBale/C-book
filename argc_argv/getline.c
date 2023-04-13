#include <stdio.h>

int getline_new(char *buf, unsigned int size) {
    int c;
    char *len = buf;

    while (--size > 0 && (c = getchar()) != EOF && c != '\n')
        *buf++ = c;
    if (c == '\n')
        *buf++ = '\n';
    *buf = '\0';

    return (int)(buf - len);
}
