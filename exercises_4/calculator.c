#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

#define MAXOP 100

int main()
{
    int type, i;
    double op2;
    char s[MAXOP];

    buffer_i = 0;
    while (getline(buffer, LIMIT) > 0) 
    {
        while ((type = getop(s)) != '\0') 
        {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case NAME:
                    mathf(s);
                    break;
                case VARIABLE:
                    getvar(s);
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else 
                        printf("error: zero divisor\n");
                    break;
                case '%':
                    op2 = pop();
                    if(op2 != 0.0)
                        push((int) pop() % (int) op2);
                    else
                        printf("error: zero divisor!\n");
                    break;
                case '?':
                    printop();
                    break;
                case 'C':
                    clear();
                    break;
                case '$':
                    swap();
                    break;
                case '\n':
                    printf("\t%.8g\n", (vars[0] = pop()));
                    break;
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
        }
        buffer_i = 0;
    }
    return 0;
}









