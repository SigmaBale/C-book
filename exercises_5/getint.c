#include <ctype.h>
#include <stdio.h>
#include "getval.h"

int getint(int *pn)
{
    int sign, temp, c;
    while(isspace(c = getch()))
        ;
    if(!isdigit(c) && c != EOF && c != '-' && c != '+') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if(c == '-' || c == '+')
        c = getch();
    if(!(isdigit(c)))
        return 0;
    for(*pn = 0; isdigit(c); c = getch())
        *pn = *pn * 10 + (c - '0');
    *pn *= sign;
    if(c != EOF)
        ungetch(c);
    return c;
}