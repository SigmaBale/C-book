#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *sdup(const char *s) {
    char *p = (char *) malloc(strlen(p)+1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}
