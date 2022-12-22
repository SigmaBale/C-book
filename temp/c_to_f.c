#include<stdio.h>

int main()
{
    float fahr, cels;
    float upper, lower, step_size;

    lower = 0;
    upper = 300;
    step_size = 20;

    printf("\nC-F conversion table\n");

    cels = lower;
    while (cels <= upper) {
        fahr = (cels / (5.0/9.0)) + 32;
        printf("%3.0f\t%6.0f\n", cels, fahr);
        cels += step_size;
    }

    return 0;
}