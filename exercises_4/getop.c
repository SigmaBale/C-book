#include <ctype.h>
#include "calculator.h"

int getop(char s[])
{
    int i, c;
    while ((s[0] = c = buffer[buffer_i++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if(islower(c)) {
        while(islower(s[++i] = buffer[buffer_i++]))
            ;
        --buffer_i;
        s[i] = '\0';
        return NAME;
    }
    if (!isdigit(c) && c != '.' && c != '-') {
        if (isupper(c) && !isalpha(s[i+1] = buffer[buffer_i])) {
            --buffer_i;
            s[i] = '\0';
            return VARIABLE;
        }
        return c;
    }
    if (isdigit(c) || c == '-')
        while (isdigit(s[++i] = c = buffer[buffer_i++]))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = buffer[buffer_i++]))
            ;
    s[i] = '\0';
    --buffer_i;
    if (i == 1 && s[0] == '.')
        return '.';
    if (i == 1 && s[0] == '-')
        return '-';
    return NUMBER;
}