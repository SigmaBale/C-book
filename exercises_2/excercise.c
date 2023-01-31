#include<stdio.h>
#define LIMIT 1000

int main()
{
    int i, c;

    for(i=0; (i < LIMIT-1) == ((c = getchar()) != '\n') == (c != EOF); ++i)
        ;

    return 0;
}