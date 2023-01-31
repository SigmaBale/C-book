#include<stdio.h>
#define BUFFER 1000

void squeeze(char s1[], char s2[]);

int main()
{
    char s1[BUFFER] = "This is a match fr.asdasdz5nrhgsvvr3";
    char s2[BUFFER] = "Nah, not amazing...";
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i, j;
    for(i = j = 0; s1[j] != '\0'; j++)
        if(s1[j] != s2[j])
            s1[i++] = s1[j];
    s1[i] = '\0';
}