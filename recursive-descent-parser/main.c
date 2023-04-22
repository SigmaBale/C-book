#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
char datatype[MAXTOKEN];
char qualifier[MAXTOKEN];
char returntype[MAXTOKEN];
int err = 0;

int main(int argc, char *argv[]) {
    int c;
    char temp[MAXTOKEN];

    if (argc > 2) {
        printf("Too many arguments provided\n");
        return 1;
    }
    if (*(++argv)[0] == '-') {
        if((c = *++argv[0]) == 'd') {
            while (gettoken() != EOF) {
                if (tokentype == QUALIFIER) {
                    strcpy(qualifier, token);
                    if (gettoken() == DATATYPE) {
                        sprintf(returntype, "%s %s", qualifier, token);
                    } else {
                        printf("Syntax error, given qualifier but missing datatype\n");
                        err = 1;
                    }
                } else if (tokentype == DATATYPE) {
                    strcpy(returntype, token);
                } else {
                    printf("Syntax error, missing datatype\n");
                    err = 1;
                }
                out[0] = '\0';
                dcl();
                if (tokentype != '\n')
                    printf("syntax error missing '\\n'\n");
                printf("%s: %s %s\n", name, out, returntype);
            }
        } else if (c == 'u') { // undcl is not working with param types and type qualifiers
            while(gettoken() != EOF) {
                strcpy(out, token);
                while (gettoken() != '\n') {
                    if (tokentype == '*') {
                        do {
                            sprintf(temp, "*%s", out); 
                            strcpy(out, temp);
                        } while (gettoken() == '*');
                        sprintf(temp, "(%s)", out);
                        strcpy(out, temp);
                    }
                    if (tokentype == PARANS || tokentype == BRACKETS) {
                        strcat(out, token);
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
