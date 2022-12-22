#include<stdio.h>

int main()
{
    int i, k, max, c;
    int counts[256];

    max = 0;

    for(i = 0; i < 256; ++i)
        counts[i] = 0;

    while((c = getchar()) != EOF)
        ++counts[c];

    for(i = 0; i < 256; ++i) {
        if(counts[i] > max)
            max = counts[i];
    }

    /* Print histogram of different chars occurences */
    for(i = 1; i <= max; ++i) {
        for(k = 0; k < 256; ++k) {
            if (counts[k] >= i)
                printf("#");
        }
        printf("\n");
    }

    return 0;
}