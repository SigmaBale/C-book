#include <stdio.h>
#define STACKSIZE 100

int stackp = 0;
double stack[STACKSIZE];

int isempty() {
    return (stackp < 1) ? 1 : 0;
}

int isfull() {
    return (stackp > STACKSIZE) ? 1 : 0;
}

void push(double n) {
    if (isfull())
        return;
    stack[stackp++] = n;
    return;
}

double pop() {
    if (isempty())
        return 0.0;
    return stack[--stackp];
}

void dumpstack(int amount) {
    int i;
    for (i = 0; amount > i; i++)
        printf("%lf%s", stack[i], (i < amount - 1) ? ", " : "");
    printf("\n\n");
}