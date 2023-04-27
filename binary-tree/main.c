#include <stdio.h>
#include <ctype.h>
#include "keycount.h"
#define LIMIT   1000

int main() {
    char word[LIMIT];
    struct treenode *p = NULL;

    while (getword(word, LIMIT) != EOF)
        if (isalpha(word[0]))
            p = addtree(p, word);
    
    printree(p);
    return 0;
}
