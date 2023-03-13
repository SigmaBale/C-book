#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include "getval.h"

int getfloat(float *pn)
{
    char c, temp;
    int sign, decimal, exponent, valid;
    while(isspace(c = getch()))
        ;
    if(!isdigit(c) && c != EOF && c != '-' && c != '+' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1.0 : 1.0;
    valid = 0;
    if(c == '-' || c == '+')
        c = getch();
    for(*pn = 0.0; isdigit(c); c = getch()) {
        *pn = *pn * 10.0 + (c - '0');
        valid = 1;
    }
    if(c == '.') {
        c = getch();
        if(!isdigit(c) && !valid)
            return 0;
    }
    for(decimal = 0; isdigit(c); c = getch(), decimal++)
        *pn = *pn * 10.0 + (c - '0');
    while(decimal-- > 0)
        *pn /= 10;
    *pn *= sign;
    if(c == 'e' || c == 'E') {
        c = getch();
        sign = (c == '-') ? -1 : 1;
        if(c == '-' || c == '+')
            c = getch();
        for(exponent = 0; isdigit(c); c = getch())
            exponent = exponent * 10 + (c - '0');
        *pn *= (sign * powf(10, exponent));
    }
    if(c != EOF)
        ungetch(c);
    return c;
}