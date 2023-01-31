#include<stdio.h>
#define FIRST_BIT (unsigned)1

unsigned rightrot(unsigned x, int n);

int main()
{
    int n = 1;
    unsigned x = 0b110;
    printf("rotated: %u\n", rightrot(x, n));
    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    int i;
    unsigned bit;
    for(i = 0; i < n; i++) {
        bit = (x & FIRST_BIT) << ((sizeof(unsigned int) * 8) - 1);
        x = (x >> 1) | bit;
    }
    return x;
}