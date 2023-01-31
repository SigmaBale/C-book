#include <stdio.h>
#include <string.h>
#include <math.h>

#define ALPHASIZE   26      /* Max amount of supported variables (en alphabet) */
#define STACKSIZE   100     /* Stack size */

double vars[ALPHASIZE];

static double val[STACKSIZE];      /* Stack where we store read values(numbers) from input stream */
static int vpos = 0;               /* Next free position/index in stack */

double pop(void)
{
    if(vpos > 0)
        return val[--vpos];
    else {
        printf("Warning: stack is empty, returning default value '0.0' this might cause unwanted results.\n");
        return 0.0;
    }
}

void push(double f)
{
    if(vpos < STACKSIZE)
        val[vpos++] = f;
    else
        printf("Error: stack is full, can't push anymore values.\n");
}

void printop(void)
{
    switch(vpos) {
        case 0:
            printf("stack is empty\n");
            break;
        case 1:
            printf("%g\n", val[0]);
            break;
        default:
            printf("%g, %g\n", val[vpos-2], val[vpos-1]);
            break;
    }
}

void dupe(void)
{
    double val = pop();
    push(val);
    push(val);
}

void swap(void)
{
    double val1 = pop();
    double val2 = pop();
    push(val1);
    push(val2);
}

void clear(void)
{   
    vpos = 0;
}

void getvar(char s[])
{
    char c = 'A';
    while(s[0] != c++)
        ;
    switch(--c) {
        case 'A':
            push(vars[0]);
            break;
        default:
            printf("This variable does not have any functionality.\n");
            break;
    }
}

void mathf(char s[])
{
    double op2;
    if(strcmp(s, "cos") == 0)
        push(cos(pop()));
    else if(strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if(strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    }
    else if(strcmp(s, "exp") == 0)
        push(exp(pop()));
    else
        printf("Function is not supported: %s\n", s);
}