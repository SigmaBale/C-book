#include <string.h>
#include "keycount.h"

struct treenode* addtree(struct treenode* root, const char* word) {
    int cmp; 
    if (root == NULL) {
        root = palloc();
        root->word = sdup(word);
        root->count = 1;
        root->left = NULL;
        root->right = NULL;
    } else if ((cmp = strcmp(word, root->word)) == 0)
        root->count++;
    else if (cmp < 0)
        root->left = addtree(root->left, word);
    else
        root->right = addtree(root->right, word);
    return root;
}
