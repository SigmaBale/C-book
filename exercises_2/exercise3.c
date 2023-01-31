#include<stdio.h>
int any(char s1[], char s2[]);

int main()
{
    int i;
    char s1[] = "xxxxXxxxxxxXXuzzzzz.";
    char s2[] = "wwwwwwwwwwpHJunddddd";
    if ((i = any(s1, s2)) == EOF)
        printf("Index not found!\n");
    else
        printf("Index = %d\n", i);
    return 0;
}

int any(char s1[], char s2[])
{
    int i, j;
    for(i = 0; s1[i] != '\0'; i++) {
        while(s2[j] != '\0')
            if(s1[i] == s2[j++])
                return i;
        j = 0;
    }
    return EOF;
}