#include <stdio.h>
#include <ctype.h>
#include "keycount.h"
#define LIMIT   1000
#define NKEYS   sizeof(keytab)/sizeof(keytab[0])

struct key keytab[] = {
    "_Alignas",         0,
    "_Alignof",         0,
    "_Atomic",          0,
    "_Bool",            0,
    "_Complex",         0,
    "_Generic",         0,
    "_Imaginary",       0,
    "_Noreturn",        0,
    "_Static_assert",   0,
    "_Thread_local",    0,
    "auto",             0,
    "break",            0,
    "case",             0,
    "char",             0,
    "const",            0,
    "continue",         0,
    "default",          0,
    "do",               0,
    "double",           0,
    "else",             0,
    "enum",             0,
    "extern",           0,
    "float",            0,
    "for",              0,
    "goto",             0,
    "if",               0,
    "int",              0,
    "long",             0,
    "register",         0,
    "return",           0,
    "short",            0,
    "signed",           0,
    "sizeof",           0,
    "static",           0,
    "struct",           0,
    "switch",           0,
    "typedef",          0,
    "unsigned",         0,
    "void",             0,
    "volatile",         0,
    "while",            0
};

int main() {
    char word[LIMIT];
    struct key *p;

    while (getword(word, LIMIT) != EOF)
        if (isalpha(word[0]) && state == OUT)
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;            

    for (p = keytab; keytab + NKEYS > p; p++)
        if (p->count > 0)
            printf("%d %s\n", p->count, p->word);

    return 0;
}
