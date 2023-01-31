#include<stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    int p, n;
    unsigned x;

    p = 5;
    n = 3;
    x = 0b11010110;

    printf("inverted: %u\n", invert(x, p, n));
    return 0;
}

unsigned invert(unsigned x, int p, int n)
{
    return (x & (~0 << p)) | (((~(x >> (p-n))) & ~(~0 << n)) << (p-n)) | (x & ~(~0 << (p-n)));
}