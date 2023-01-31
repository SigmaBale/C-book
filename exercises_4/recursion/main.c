#include <stdio.h>
#include "r_itoa.h"

int main()
{
    char s[100];
    int n = 21474836;

    r_itoa(n, s);
    printf("%s\n", s);

    return 0;
}