#include <stdio.h>
#include <ctype.h>
#include "keycount.h"

int state = OUT;

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
    while (isspace(c = getch())) {
        if (state == PREPROC)
            state = OUT;
        else if (state == HYPHEN)
            state = OUT;
        else if (state == STAR)
            state = COMMENT;
    }
    if (c != EOF)
        *str++ = c;
    if (!isalpha(c) && c != '_') {
        switch (c) {
            case '"':
                if (state == OUT)
                    state = STRCONST;
                else if (state == STRCONST)
                    state = OUT;
                break;
            case '/':
                if (state == OUT)
                    state = HYPHEN;
                else if (state == STAR)
                    state = OUT;
                break;
            case '*':
                if (state == HYPHEN)
                    state = COMMENT;
                else if (state == COMMENT)
                    state = STAR;
                break;
            case '#':
                if (state == OUT)
                    state = PREPROC;
                break;
            default:
                break;
        }
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
