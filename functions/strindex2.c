#include<stdio.h>
#define MAXSIZE 1000

char pattern[] = "ould";

int getline(char b[], int size);
int strindex(char s[], char p[]);

int main()
{
    char buffer[MAXSIZE];
    char last[MAXSIZE];
    int i, k, c, sidx, lidx, lastidx, sum;
    
    lastidx = -1;
    sum = 0;
    while((lidx = getline(buffer, MAXSIZE)) > 0) {
        if((sidx = strindex(buffer, pattern)) >= 0) {
            for(k = 0; (last[k] = buffer[k]) != '\0'; k++)
                ;
            lastidx = sum + sidx;
        }
        sum += lidx;
    }
    if(lastidx >= 0)
        printf("%s", last);
    return lastidx;
}

int getline(char buffer[], int limit)
{
    int c, i;
    i = 0;
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