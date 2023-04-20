#include <stdio.h>

static int c;
static int empty = 1;

int getch() {
    if (empty)
        return getchar();
    empty = 1;
    return c;
}

void ungetch(char ch) {
    empty = 0;
    c = ch;
}
