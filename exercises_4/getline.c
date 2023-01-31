#include <stdio.h>

#define LIMIT 1000

char buffer[LIMIT];         /* Line buffer */
int buffer_i;               /* Current position/index in line buffer */

int getline(char s[], int size)
{
    int i, c;
    i = 0;
    while(--size > i && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if(c == '\n')
        s[i++] = '\n';
    s[i] = '\0';
    return i;
}