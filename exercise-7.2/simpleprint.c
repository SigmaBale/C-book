#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define COLLIMIT 60
#define NEWLINE  10
#define HORTAB   9

int
main(void)
{
    int c, col;

    for(col = 0; (c = getchar()) != EOF; col++) {
        if(col >= COLLIMIT || c == NEWLINE) {
            putchar('\n');
            col = 0;
            if(c == NEWLINE)
                continue;
        }
        if(c != HORTAB && c < 32 || c > 127)
            printf("%X", c);
        else
            putchar(c);
    }
    return 0;
}
