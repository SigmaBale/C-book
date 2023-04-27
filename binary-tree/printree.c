#include <stdio.h>
#include "keycount.h"

void printree(struct treenode *tree) {
    if (tree != NULL) {
        printree(tree->left);
        printf("%4d, %s\n", tree->count, tree->word);
        printree(tree->right);
    }
}
