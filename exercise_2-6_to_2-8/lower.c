#include<stdio.h>
#define OFFSET 32

void lower(char s[]);

int main()
{
    char buffer[] = "THIS Should ALL BE LOWERCASE.";
    lower(buffer);
    printf("%s\n", buffer);
    return 0;
}

void lower(char s[])
{
    int i = 0;
    while(s[i] != '\0')
        s[i++] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + OFFSET : s[i];
}