/*Copy the n lowest bits from y into x, at position p*/
#include<stdio.h>

unsigned setbits(unsigned x, unsigned y, int n, int p);

int main()
{
    int p, n;
    unsigned x, y;

    p = 5;
    n = 3;

    x = 0b01001000; /* 01111000 */
    y = 0b10110111;

    x = setbits(x, y, n, p);
    printf("x = %u\n", x);
    return 0;
}

unsigned setbits(unsigned x, unsigned y, int n, int p)
{
    return (x & (~0 << p)) | ((y & ~(~0 << n)) << (p-n)) | (x & ~(~0 << (p-n)));
}