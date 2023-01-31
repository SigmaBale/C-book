#include<stdio.h>
#include<ctype.h>

#define SIZE        1000
#define CHAINED     1
#define UNCHAINED   0
#define SEPARATOR   '-'

void expand(char to[], char from[]);

int main()
{
    char buffer[SIZE];
    char s[] = "This range -a-z and this0-100A-G and also a-b-c. Very good f-a";
    expand(buffer, s);
    printf("%s\n", buffer);
    return 0;
}

void expand(char buffer[], char s[])
{
    int i, j, end, mid, start, chain;
    
    chain = UNCHAINED;
    for(i = j = 0; s[i] != '\0'; i++) {
        start = s[i], mid = s[i+1], end = s[i+2];
        if(((isalpha(start) && isalpha(end)) 
                || (isdigit(start) && isdigit(end))) 
                && mid == SEPARATOR 
                && start < end)
        {
            if(!chain)
                buffer[j] = start;
            while(start < end)
                buffer[++j] = ++start;
            i+=1;
        }
        else {
            if(chain) {
                chain = UNCHAINED;
                continue;
            }
            buffer[j++] = start;
        }
    }
    buffer[j] = '\0';
}