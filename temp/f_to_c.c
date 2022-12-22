#include<stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP  20

float fahr_to_cels(float f);

/* Print Faranheit - Celsius table
        for fahr = 0, 20, 40, ..., 300*/
int main() 
{
    float fahr, cels;

    printf("\nF-C conversion table\n");
    for(fahr = LOWER; fahr <= UPPER; fahr += STEP)
        printf("%3.0f\t %3.1f\n", fahr, fahr_to_cels(fahr));

    return 0;
}

float fahr_to_cels(float fahr) 
{
    return (5.0/9.0) * (fahr - 32.0);
}