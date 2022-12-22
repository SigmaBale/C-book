#include<stdio.h>

#define LOWER 0         /* Symbolic name/constant 1*/
#define UPPER 300       /* Symbolic name/constant 2*/
#define STEP 20    /* Symbolic name/constant 3*/

int main() {
    int fahr;

    for (fahr = UPPER; fahr >= LOWER; fahr -= STEP)
        printf("%3d\t%6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}