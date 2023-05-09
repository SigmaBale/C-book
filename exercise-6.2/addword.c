#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "treenode.h"

struct treenode* addword(struct treenode* root, char* word) {
    int cmp;

    if (root == NULL) {
        root = talloc();
        root->word = sdup(word);
        root->left = NULL;
        root->right = NULL;
    } else if ((cmp = strcmp(word, root->word)) > 0) /* Omit equal comparison, we don't care about count */
        root->right = addword(root->right, word);
    else if (cmp < 0)
        root->left = addword(root->left, word);
    return root;
}
