#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER 0

void push(double n);
double pop();

int main(int argc, char *argv[]) {
    int type, c;
    double op1, op2;

    while (--argc > 0) {
        c = **++argv;
        if (!isdigit(c) && strlen(*argv) == 1)
            type = c;
        else
            type = NUMBER;
        switch (type) {
            case NUMBER:
                push(atof(*argv));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                push(pop() - pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero division\n");
                break;
            case '%':
                op2 = pop();
                if (op2 == 0)
                    printf("error: undefined behaviour modulo with 0");
                else
                    push(fmod(pop(), op2));
                break;
            case '^':
                op2 = pop();
                op1 = pop();
                if (op1 == 0 && op2 <= 0)
                    printf("error: if x = 0.0 then exponent must be greater than 0\n");
                else
                    push(pow(op1, op2));
                break;
            default:
                printf("Unkown command: %c\n", type);
                break;
        }
    }
    printf("\t%.8g\n", pop());
    return 0;
}