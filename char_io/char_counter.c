#include<stdio.h>

int main()
{
    int c, nl, blank, tab, lastc;

    blank = 0;
    tab = 0;
    nl = 0;
    while ((c = getchar()) != 'p') {
        if (c == '\n') {
            ++nl;
            putchar(c);
        }
        else if (c == '\t') {
            ++tab;
            putchar('\\');
            putchar('t');
        }
        else if (c == ' ') {
            ++blank;
            if (lastc != c)
                putchar(c);
        }
        else if (c == '\b') {
            putchar('\\');
            putchar('b');
        }
        else if (c == '\\') {
            putchar('\\');
            putchar('\\');
        }
        else 
            putchar(c);

        lastc = c;
    }

    printf("New lines: %d, Blanks: %d, Tabs: %d\n", nl, blank, tab);

    return 0;
}