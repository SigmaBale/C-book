#include <stdio.h>

size_t getline(char *buf, unsigned int size) {
    int c;
    size_t len = buf;

    while (--size > 0 && (c = getchar()) != EOF && c != '\n')
        *buf++ = c;
    if (c == '\n')
        *buf++ = '\n';
    *buf = '\0';

    return (size_t)(buf - len);
}