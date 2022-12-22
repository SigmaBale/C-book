#include<stdio.h>

int main() 
{
    int c;

    printf("%d\n", EOF); /* EOF is not a printable char, it is defines as int (-1) */

    while (0 != (1 == ((c = getchar()) != EOF))) /* Just following the book that asked me to verify */
        putchar(c);                              /* the value of comparison for either a 1 or 0 */
}