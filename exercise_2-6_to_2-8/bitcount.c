#include<stdio.h>

int bitcount(unsigned x);

int main()
{
    unsigned x = 0b1001110010111;
    printf("Bitcount: %d\n", bitcount(x));
    return 0;
}

int bitcount(unsigned x)
{
    int i;
    for(i = 0; x > 0; x &= (x - 1))
        i++;
    return i;
}