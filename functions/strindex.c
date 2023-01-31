#include<stdio.h>
#define MAXSIZE 1000

char pattern[] = "ould";

int getline(char b[], int size);
int strindex(char s[], char p[]);

int main()
{
    char buffer[MAXSIZE];
    int found = 0;

    while(getline(buffer, MAXSIZE) > 0) {
        if(strindex(buffer, pattern) >= 0) {
            printf("%s", buffer);
            found++;
        }
    } 
    return found;
}

int getline(char buffer[], int limit)
{
    int c, i;
    while(--limit > 0 && (c = getchar()) != EOF && c != '\n')
        buffer[i++] = c;
    if(c == '\n')
        buffer[i++] = '\n';
    buffer[i] = '\0';
    return i;
}

int strindex(char s[], char pat[])
{
    int i, j, k;
    for(i = 0; s[i] != '\0'; i++) {
        for(j=i, k=0; pat[k] != '\0' && pat[k] == s[j]; j++, k++)
            ;
        if(k > 0 && pat[k] == '\0')
            return i;
    }
    return -1;
}