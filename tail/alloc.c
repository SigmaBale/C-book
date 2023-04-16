#include <stdio.h>
#define SIZE 100000

char abuf[SIZE];
char *apt = abuf;

char *alloc(unsigned int len) {
    if (apt + len > abuf + SIZE)
        return NULL;

    apt += len;
    return apt - len;
}

void afree(char *p) {
    if (apt > p && p > abuf)
        apt = p; 
}
