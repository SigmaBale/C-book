#include <stdio.h>
#include <string.h>
#include "parser.h"
void paramls(void);
char name[MAXTOKEN];
char out[1000];
int plist = 0;

void dirdcl(void) {
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("Syntax error, missing ')'\n");
            err = 1;
        }
    } else if (tokentype == NAME)
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        err = 1;
    }
    while (gettoken() == PARANS || tokentype == BRACKETS || tokentype == '(') {
        if (tokentype == PARANS)
            strcat(out, " function returning");
        else if (tokentype == '(') {
            paramls();
        } else {
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

/* I could use return as soon as error is encountered but doing it this way was fun */
void paramls(void) {
    char temp[1000];
    temp[0] = '\0';
    strcat(temp, " function expecting");
    do {
        if (tokentype == ',')
            strcat(temp, ",");
        if (gettoken() == QUALIFIER || tokentype == DATATYPE) {
            if (tokentype == QUALIFIER) {
                strcpy(qualifier, token);
                if (gettoken() != DATATYPE) {
                    printf("Syntax error, qualifier given but missing datatype\n");
                    err = 1;
                } else {
                    strcat(temp, " ");
                    strcat(temp, qualifier);
                    strcat(temp, token);
                }
            } else {
                strcat(temp, " ");
                strcat(temp, token);
            }
        } else {
            printf("Syntax error, expected function parameter type got '%s'\n", token);
            err = 1;
        }
    } while (!err && gettoken() == ',');
    if (!err && tokentype != ')') {
        printf("Syntax error, missing ')'\n");
        err = 1;
    } 
    if (!err) {
        strcat(out, temp);
        strcat(out, " returning");
    }
    return;
}
