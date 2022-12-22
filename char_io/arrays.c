#include<stdio.h>

int main()
{
    int ndigits[10];
    int c, i, k, nwhite, nother, max;

    nwhite = nother = max = 0;

    for(i = 0; i < 10; ++i)
        ndigits[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else if (c >= '0' && c <= '9')
            ++ndigits[c - '0'];
        else
            ++nother;
    }

    /* Get max */
    for(i = 0; i < 10; i++) {
        if (ndigits[i] > max)
            max = ndigits[i];
    }

    /* Vertical bars histogram for number occurences */
    for(i = 1; i <= max; i++) {
        for (k = 0; k < 10; ++k) {
            if (ndigits[k] >= i) {
                putchar('#');
            }
            else
                putchar(' ');
        }
        putchar('\n');
    }

    printf("Number of whitespace chars: %d\n", nwhite);
    printf("Number of other chars: %d\n", nother);

    return 0;
}