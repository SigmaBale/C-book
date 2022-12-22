#include<stdio.h>

#define IN  1
#define OUT 0

int main()
{
    int buffer[512];
    int i, k, word, c, lastidx, len, max;

    for(i = 0; i < 512; ++i)
        buffer[i] = 0;

    word = OUT;
    lastidx = len = max = 0;

    while((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == ' ') {
            if (word == IN) {
                buffer[lastidx] = len;
                ++lastidx;
            }
            word = OUT;
            len = 0;
        }
        else if (word == IN)
            ++len;            
        else {
            word = IN;
            ++len;
        }   
    }

    /* Get max len word */
    for(i = 0; i <= lastidx; ++i) {
        if(buffer[i] > max)
            max = buffer[i];
    }

    /* Print histogram of word lengths */
    for(i = 1; i <= lastidx; ++i)
        printf("%3d", i);

    printf("\t\b\b\b\b<- Word order\n");
    for(i = 1; i <= max; ++i) {
        for(k = 0; k < lastidx; ++k) {
            if (buffer[k] >= i)
                printf("%3c", '#');
            else
                printf("%3c", ' ');
        }
        printf("\t\b\b\b\b<- Length %d\n", i);
    }

    return 0;
}