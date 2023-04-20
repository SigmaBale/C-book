#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parray.h"
#define MAXLINES 2000
char *lineptr[MAXLINES];
int numcmp(const char *, const char *);
int dircmp(const char *, const char *);
int stoi(char *);

int main(int argc, char *argv[]) {
    int lines;
    int dir, numeric;
    char *ap;
    flags options = { (int (*)(void *, void *)) strcmp, 0, 0, 0 }; 

    numeric = dir = 0;
next_arg:
    while (--argc && *(++argv)[0] == '-') {
        ap = ++(argv[0]);
        while ((*ap)) {
            switch (*ap) {
                case 'n':
                    if (dir) {
                        printf("Flag 'n' (numeric) incompatible with 'd' (dirord)\n");
                        return 1;
                    }
                    numeric = 1;
                    options.cmp = (int (*)(void *, void *)) numcmp;
                    break;
                case 'r':
                    options.reverse = 1;
                    break;
                case 'f':
                    options.fold = 1;
                    break;
                case 'd':
                    if (numeric) {
                        printf("Flag 'd' (dirord) incompatible with 'n' (numeric)\n");
                        return 1;
                    }
                    dir = 1;
                    options.cmp = (int (*)(void *, void *)) dircmp;
                    break;
                case 's': {
                    char *pdelim = ap+1;
                    if (*pdelim == '\0') {
                        if (argc < 2) {
                            printf("Missing argument at flag 's'\n");
                            return 1;
                        }
                        pdelim = *(++argv);
                        argc--;
                    }
                    strncpy(options.delim, pdelim, MAXLINE);
                    options.field = stoi(*(++argv));
                    argc--;
                    if (options.field == -1) { 
                        printf("Invalid field number at flag 's'\n");
                        return 1;
                    }
                    goto next_arg;
                }
                default:
                    printf("Invalid arg '%c'\n", *ap);
                    return 1;
            }
            ap++;
        }
    }
    if ((lines = readlines(lineptr, MAXLINES)) < 0) {
        printf("Error: Can't read any more lines, too much input!\n");
        return 1;
    }
    quicksort((void**) lineptr, 0, lines - 1, &options);
    printarray(lineptr, lines);
    return 0;
}

int numcmp(const char *str1, const char *str2) {
    double num1, num2;

    num1 = atof(str1); 
    num2 = atof(str2); 

    if (num1 < num2)
        return -1;
    else if (num1 > num2)
        return 1;
    else
        return 0;
}

int dircmp(const char *str1, const char *str2) {
    while ((*str1 && *str2)) {
        if (!isalnum(*str1) && !isblank(*str1)) {
            str1++;
            continue;
        }
        if (!isalnum(*str2) && !isblank(*str2)) {
            str2++;
            continue;
        }

        if(*str1 < *str2)
            return -1;
        else if(*str1 > *str2)
            return 1;
        else
            str1++, str2++;
    }
    return 0;
}

int stoi(char *str) {
    int num, c;
    for (num = 0; isdigit((c = *str)); str++)
        num = num * 10 + (c - '0');
    if (*str != '\0')
        return -1;
    return num;
}
