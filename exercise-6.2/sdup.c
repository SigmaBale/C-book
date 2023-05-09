#include <stdlib.h>
#include <string.h>

char* sdup(char* s) {
    char* p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}
