#include <stdio.h>
#include "tail.h"
#define MAXLINES 1000

int main(int argc, char *argv[]) {
    int c;
    int lines;
    char *buff[MAXLINES];
    int bufp;
    int i, j;
    int start;

    lines = 10;
    while(--argc && *(++argv)[0] == '-') {

        c = (*argv)[1];
        if (c == 'n') {
            if(parse_lines(&(*argv)[2], &lines) == 0)
                continue;
            if(argc-- > 1 && parse_lines(*(++argv), &lines) == 0)
                continue;
        }
        printf("tail: error at flag 'n'\n");
        return 1;
    }

    if (lines < 0) {
        printf("tail: number of lines can't be negative\n");
        return 1;
    }

    bufp = 0;
    if (write_lines(buff, &bufp) == 1) {
        printf("Can't write anymore lines, overflow\n");
        return 1;
    }

    printf("bufp = %d, lines = %d\n", bufp, lines);
    if((start = bufp - lines) < 0)
        start = 0;
    for (i = 1; start < bufp; start++, i++)
        printf("%d. %s\n", i, buff[start]);

    return 0;
}
