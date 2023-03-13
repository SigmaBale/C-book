#include <stdio.h>

static char buff = ' ';

int getch(void)
{
    return (buff != ' ') ? buff : getchar();
}

void ungetch(int c)
{
    buff = c;
    return;
}