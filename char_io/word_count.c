#include<stdio.h>

#define OUT     0
#define IN      1
#define NEWLINE 2
#define OLDLINE 3

int main() 
{
    int c, nw, nl, nc, state, line, lastwc;
    
    nl = nc = nw = lastwc = 0;
    state = OUT;
    line = NEWLINE;

    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n') {
            line = NEWLINE;
            lastwc = nw;
            putchar('\n');
            ++nl;
        }
        if (c == '\n' || c == '\t' || c == ' ') {
            state = OUT;
            if (lastwc < nw)
                line = OLDLINE;
        }
        else if (state == OUT) {
            state = IN;
            ++nw;
            if (line == NEWLINE)
                putchar(c);
        } 
        else if (line == NEWLINE)
            putchar(c);
    }
    printf("%d %d %d\n", nl, nw, nc);
}