#include<stdio.h>

int power(int m, int n);

int main()
{
    printf("%d\n", power(2, 4));

    return 0;
}

int power(int base, int n)
{
    int i, p;

    p = 1;
    for(i = 0; i < n; ++i)
        p = p * base;
    return p;
}