#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#define TYPES 5
int tokentype;
int i;
char token[MAXTOKEN];

int gettoken(void) {
    static char *datatypes[TYPES] = { "char", "int", "float", "double", "void" };
    int c;
    char *p = token;

    if (err) {
        err = 0;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        while ((c = getch()) == ' ' || c == '\t')
            ;
        if (c  == ')') {
            strcpy(token, "()");
            return tokentype = PARANS;
        }
        ungetch(c);
        return tokentype = '(';
    } else if (c == '[') {
        for (*p++ = c; (*p = getch()) != ']' && *p != '[' && *p != '\n'; p++)
            ;
        if (*p == '[' || *p == '\n') {
            printf("Syntax error, missing ']'\n");
            err = 1;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum((c = getch())); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        if (strcmp(token, "const") == 0 || strcmp(token, "volatile") == 0) {
            return tokentype = QUALIFIER;
        }
        for (i = 0; i < TYPES; i++) {
            if (strcmp(token, datatypes[i]) == 0) {
                return tokentype = DATATYPE;
            }
        }
        return tokentype = NAME;
    } else
        return tokentype = c;
}
