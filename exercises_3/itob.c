#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OFFSET  87
#define HEX     16
#define SIZE    1000

void itob(int n, int b, char s[]);

int main()
{
    int n = INT_MIN;
    int b = 16;
    char buffer[SIZE];
    itob(n, b, buffer);
    printf("%s\n", buffer);
    return 0;
}

void itob(int num, int base, char buffer[])
{
    int i, sign, digit;
    digit = sign = 0;
    if((sign = num) < 0)
        num = -num;
    do
    {
        if(base == HEX && (digit = abs(num % base)) > 9)
            digit += OFFSET;
        else
            digit = abs(num % base) + '0';
        buffer[i++] = digit;
    } while ((num/=base) != 0);
    if(sign < 0)
        buffer[i++] = '-';
    buffer[i] = '\0';
    strrev(buffer);
}