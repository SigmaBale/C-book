/*
int detab(char s[], char new[])
{
    int i, j, k;

    i = k = 0;
    while((new[i] = s[k]) != '\0') {
        if(new[i] == '\t') {
            for(j = i; j < ((i + SPACE) / SPACE * SPACE); ++j)
                new[j] = ' ';
            i = j-1;
        }
        ++i;
        ++k;
    }
    return i;
}
*/

#include "expand.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT_TABSIZE 8

int main(int argc, char *argv[]) {
    int tablist[TABLIST_SIZE];
    int preceeding;
    int specifier;
    int tabsize;
    int len;
    int result;

    tabsize = DEFAULT_TABSIZE;
    specifier = len = 0;

    if ((result = parse_args(argc, argv, tablist, &len, &specifier, &preceeding)) == -1)
        return 1;
    if (result == 0)
        return 0;

    return 0;
}
