#include<stdio.h>
#define BUFFER_SIZE 1000

int get_line(char buffer[], int len);
int trim(char old[], char new[]);

int main()
{
    int i, len, k, nlen;
    char buffer[BUFFER_SIZE];
    char trimmed[BUFFER_SIZE];

    i = 0;
    while((len = get_line(buffer, BUFFER_SIZE)) > 0) {
        nlen = trim(buffer, trimmed);
        printf("%s\n", trimmed);
        printf("old len: %d, new len: %d\n", len, nlen);
    }

    return 0;
}

int get_line(char b[], int size) /* Always returns null terminated char array */
{
    int i, c;

    for(i = 0; (c = getchar()) != EOF && i <= size && c != '\n'; ++i)
        b[i] = c;
    if (c == '\n') {
        b[i] = c;
        ++i;                /* Possible index out of range when adding null */
    }
    if (i <= size)          /* So we check i again */
        b[i] = '\0';        /* If in bounds append null char */
    else {
        b[i-1] = '\0';      /* If there is no space for null char, overwrite the last char */
        --i;
    }
    return i;
}

int trim(char old[], char new[]) /* Works only with char arrays that contain \0 at the end */
{
    int i, c, k, nl;

    i = 0;
    while(old[i] != '\0')
        ++i;
    --i;
    while(((c = old[i]) == ' ' || c == '\t' || c == '\n') && i >= 0) {
        if (i == 0) {
            new[i] = '\0';  /* Add null terminator at index 0 */
            return i;
        }
        --i;
    }
    for(k = 0; k <= i; ++k)
        new[k] = old[k];
    ++i;
    new[i] = '\0';          /* Add null terminator */
    return i;               /* Return new len */
}