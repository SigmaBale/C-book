#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define SIZE 1000

void itoa_1(int n, char s[]);
void itoa_2(int n, int width, char s[]);

int main()
{
    int n = -51274;
    char buffer[SIZE];
    itoa_2(n, 7, buffer);
    printf("%s\n", buffer);
    return 0;
}

void itoa_1(int n, char buffer[])
{
    int i, sign;

    i = 0;
    if((sign = n) < 0)
        n = -n;
    do
    {
        buffer[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if(sign < 0)
        buffer[i++] = '-';
    buffer[i] = '\0';
    strrev(buffer);
}

void itoa_2(int n, int width, char buffer[])
{
    int i, sign;

    i = 0;
    if((sign = n) < 0)
        n = -n;
    do
    {
        buffer[i++] = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if(sign < 0)
        buffer[i++] = '-';
    while(i < width)
        buffer[i++] = ' ';
    buffer[i] = '\0';
    strrev(buffer);
}