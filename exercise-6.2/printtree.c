#include <stdio.h>
#include "treenode.h"

void printtree(struct treenode *tree) {
    if (tree != NULL) {
        printtree(tree->left);
        printf("%s\n", tree->word);
        printtree(tree->right);
    }
}
