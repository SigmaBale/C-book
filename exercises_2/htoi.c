#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#define OFFSET 10
#define BASE   16

int htoi(char s[]);

int main()
{
    char s[] = "0xf1beef";
    int dec = htoi(s);
    
    printf("Decimal: %d\n", dec);

    return 0;
}

int htoi(char s[])
{
    int dec, i, len, digit, y, c;

    len = strlen(s);
    dec = digit = y = 0;
    for(i = len-1; i >= 0; --i) {
        c = tolower(s[i]);
        if((i == 0 && c == '0') || (i == 1 && c == 'x'))
            continue;
        else if(c >= 'a' && c <= 'f') 
            digit = c - 'a' + OFFSET;
        else if(c >= '0' && c <= '9')
            digit = c - '0';
        else {  
            printf("Invalid char %c\n", c);
            return i;
        }
        dec += digit * pow(BASE, y++);
    }
    return dec;
}