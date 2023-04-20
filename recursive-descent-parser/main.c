#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
char datatype[MAXTOKEN];

int main(int argc, char *argv[]) {
    int c;
    char temp[MAXTOKEN];

    if (argc > 2) {
        printf("To many arguments provided\n");
        return 1;
    }
    if (*(++argv)[0] == '-') {
        if((c = *++argv[0]) == 'd') {
            while (gettoken() != EOF) {
                strcpy(datatype, token);
                out[0] = '\0';
                dcl();
                if (tokentype != '\n')
                    printf("syntax error missing newline\n");
                printf("%s: %s %s\n", name, out, datatype);
            }
        } else if (c == 'u') {
            while(gettoken() != EOF) {
                strcpy(out, token);
                while (gettoken() != '\n') {
                    if (tokentype == PARANS || tokentype == BRACKETS) {
                        strcat(out, token);
                    } else if (tokentype == '*') {
                        sprintf(temp, "(*%s)", out);
                        strcpy(out, temp);
                    } else if (tokentype == NAME) {
                        sprintf(temp, "%s %s", token, out);
                        strcpy(out, temp);
                    } else
                        printf("Invalid input\n");
                }
                printf("%s\n", out);
            }
        }
    }
    return 0;
}
