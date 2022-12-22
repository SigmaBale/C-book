#include<stdio.h>
#define SIZE 1000

int get_line(char buffer[], int len);
void reverse(char s[]);

int main()
{
    int len;
    char buffer[SIZE];

    while((len = get_line(buffer, SIZE) > 0)) {
        reverse(buffer);
    }

    return 0;
}

int get_line(char b[], int size) /* Always returns null terminated char array */
{
    int i, c;

    for(i = 0; (c = getchar()) != EOF && i < size - 1 && c != '\n'; ++i)
        b[i] = c;
    if (c == '\n') {
        b[i] = c;
        ++i;
    }
    b[i] = '\0';
    return i;
}

void reverse(char s[]) /* Reverses a char string */
{
    int i, len, c;
    char rev[1000];

    len = 0;
    while((c = s[len]) != '\0')
        ++len;
    i = 0;
    --len;
    while(i <= len) {
        rev[i] = s[len - i];
        ++i;
    }
    rev[len + 1] = '\0';            /* Add null terminator */
}