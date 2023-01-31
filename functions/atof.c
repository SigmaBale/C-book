#include<stdio.h>
#include<ctype.h>
#include<math.h>
#define MAXLINE 1000

double atof_exercise(char s[]);

int main()
{
    char buffer[] = "-152.32E-7";
    printf("val = %g\n", atof_exercise(buffer));
    return 0;
}

double atof_exercise(char s[])
{
    int sign, esign, i, e;
    double value, power;

    for(i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if(s[i] == '+' || s[i] == '-')
        i++;
    for(value = 0.0; isdigit(s[i]); i++)
        value = value * 10.0 + (s[i] - '0');
    if(s[i] == '.')
        i++;
    for(power = 1.0; isdigit(s[i]); i++) {
        value = value * 10.0 + (s[i] - '0');
        power *= 10;
    }
    value = (sign * (value / power));
    if(s[i] == 'e' || s[i] == 'E') {
        i++;
        esign = (s[i] == '-') ? -1 : 1;
        if(s[i] == '-' || s[i] == '+')
            i++;
        for(e = 0; isdigit(s[i]); i++)
            e = e * 10 + (s[i] - '0');
        e = e * esign;
        while(e < 0) {
            value *= 0.1;
            e++;
        }
        while(e > 0) {
            value *= 10;
            e--;
        }
    }
    return value;
}