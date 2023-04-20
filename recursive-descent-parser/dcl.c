#include <stdio.h>
#include <string.h>
#include "parser.h"
char name[MAXTOKEN];
char out[1000];

void dirdcl(void) {
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("Syntax error, missing ')'\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    while ((type = gettoken()) == PARANS || type == BRACKETS) {
        if (type == PARANS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

void dcl(void) {
    int ns;

    for (ns = 0; gettoken() == '*'; ns++)
        ;
    dirdcl();
    while(ns--)
        strcat(out, " pointer to");
}
