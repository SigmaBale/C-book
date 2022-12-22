#include<stdio.h>
#define MINIMUM       80
#define BUFFER_SIZE   1000  

int get_line(char buffer[], int size);

int main()
{
    int len;
    char buffer[BUFFER_SIZE];

    while((len = get_line(buffer, BUFFER_SIZE)) > 0) {
        if (len >= MINIMUM)
            printf("%s\n", buffer);
    }

    return 0;
}

int get_line(char b[], int size)
{
    int i, c;

    for(i = 0; (c = getchar()) != EOF && i <= size && c != '\n'; ++i)
        b[i] = c;
    if (c == '\n') {
        b[i] = c;
        ++i; /* Possible index out of range when adding null */
    }
    if (i <= size) /* So we check i again */
        b[i] = '\0';
    return i;
}

