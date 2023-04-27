#include <stdio.h>
#include <ctype.h>
#include "keycount.h"

static int bufch = ' ';
static int empty = 1;

int getch(void) {
    if (empty)
        return getchar();
    empty = 1;
    return bufch;
}

void ungetch(int c) {
    empty = 0;
    bufch = c;
}

int getword(char *p, int size) {
    int c;
    char *str = p;

    *str = '\0';
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *str++ = c;
    if (!isalpha(c) && c != '_') {
        *str = '\0';
        return c;
    }
    for (; --size; str++)
        if (!isalnum(*str = getch())) {
            ungetch(*str);
            break;
        }
    *str = '\0';
    return p[0];
}
