#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

size_t getline(char *buffer, unsigned int size);

int main(int argc, char *argv[]) {
    const char *line[MAXLINE];
    int found, c, except, number, lineno;

    found = except = number = lineno = 0;
    while (--argc > 0 && *(++argv)[0] == '-') {
        while (c = *++argv[0])
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("Illegal option: %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
    }

    if (argc != 1)
        printf("Usage: find -x -n 'pattern'\n");
    else
        while (getline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s\n", line);
                found++;
            }
        }
    return found;
}
