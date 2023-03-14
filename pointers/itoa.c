#include <math.h>
#include <string.h>
void itoa_1(int n, char *p) {
    int sign;
    if((sign = n) < 0)
        n = -n;
    do
    {
        *p++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if(sign < 0)
        *p++ = '-';
    *p = '\0';
    strrev(p);
}

void itoa_2(int n, char *p, int width) {
    int sign;
    if((sign = n) < 0)
        n = -n;
    do
    {
        *p++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if(sign < 0)
        *p++ = '-';
    while(width--)
        *p++ = ' ';
    *p = '\0';
    strrev(p);
}