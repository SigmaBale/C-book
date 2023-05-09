#include "treenode.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum state          state = OUT;
enum type           type = NONE;
static unsigned int escape = 0;

int buf;
int gotval = 0;

int getch(void) {
    if (!gotval)
        return getchar();
    gotval = 0;
    return buf;
}

void ungetch(int c) {
    gotval = 1;
    buf = c;
}

void prev_state() {
    if (state != OUT) {
        if (state == STAR)
            state = COMMENT;
        else if (state == SLASH)
            state = OUT;
    }
    escape = 0;
}

int getword(char* s, unsigned int size) {
    int   c, space, start_size;
    char* str = s;

    start_size = size;
    while (isspace(c = getch()))
        space = 1;
    if (space) {
        prev_state();
        if (state == PREPROC)
            state = OUT;
        space = 0;
    }

    if (c != EOF)
        *str++ = c;
    if (!isalpha(c)) {
        switch (c) {
        case '"':
            if (!escape) {
                if (state == OUT)
                    state = STRLIT;
                else if (state == STRLIT)
                    state = OUT;
            }
            break;
        case '/':
            if (!escape) {
                if (state == OUT)
                    state = SLASH;
                else if (state == STAR)
                    state = OUT;
            }
            break;
        case '*':
            if (state == SLASH && !escape)
                state = COMMENT;
            else if (state == COMMENT)
                state = STAR;
            break;
        case '#':
            if (state == OUT && !escape)
                state = PREPROC;
            break;
        case '\\':
            escape = (escape == 0 ? 1 : 0);
            break;
        default:
            break;
        }
        *str = '\0';
        return c;
    }
    for (; --size; str++)
        if (!isalnum(*str = getch()) && *str != '_') {
            ungetch(*str);
            break;
        }
    *str = '\0';

    prev_state();

    if (state == OUT) {
        if (strcmp(s, "char") == 0)
            type = CHAR;
        else if (strcmp(s, "int") == 0)
            type = INT;
        else if (strcmp(s, "float") == 0)
            type = FLOAT;
        else if (strcmp(s, "double") == 0)
            type = DOUBLE;
        else if (strcmp(s, "long") == 0)
            type = LONG;
        else
            type = NONE;

        if (type != NONE)
            getword(s, start_size);
    } else
        s[0] = '^';

    return s[0];
}
