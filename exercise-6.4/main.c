#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD (unsigned int) 1000

struct vector {
    void**       ptr;
    unsigned int size;
};

struct key {
    char*        value;
    unsigned int count;
};

struct treenode {
    struct key*      key;
    struct treenode* left;
    struct treenode* right;
};

struct tree {
    struct treenode* root;
    unsigned int     count;
    unsigned int     inserted_flag : 1;
};

typedef struct vector   Vector;
typedef struct key      Key;
typedef struct treenode Treenode;
typedef struct tree     Tree;

Vector* vec_new(void**, unsigned int);
void    vec_free(Vector*);
void    vec_print(Vector*);

Treenode* treenode_insert(Tree*, Treenode*, char*, int (*)(void*, void*));
void      treenode_freeall(Treenode*);
void      treenode_free(Treenode*);
void      treenode_into_refvec(Vector*, Treenode*);

Tree*        tree_new(void);
Tree*        tree_insert(Tree*, char*, int (*)(void*, void*));
unsigned int tree_size(Tree*);
Vector*      tree_into_refvec(Tree*);

void tree_free(Tree*);
int  getword(char*, unsigned int);
void swap(Vector*, unsigned int, unsigned int);
void quicksort(Vector*, int, int, int (*)(void*, void*));
int  qs_partition(Vector*, int, int, int (*)(void*, void*));
int  cmpkey(Key*, Key*);
int  getch(void);
void ungetch(char c);

int          chbuff;
unsigned int empty = 1;

int
main()
{
    char         word[MAXWORD];
    Tree*        tree = NULL;
    Vector*      vec  = NULL;
    unsigned int vec_size;

    while(getword(word, MAXWORD) != EOF) {
        if(isalpha(word[0]) || word[0] == '_' && strlen(word) > 1) {
            tree = tree_insert(tree, word, (int (*)(void*, void*)) strcmp);
            assert(tree != NULL);
        }
    }

    if((vec = tree_into_refvec(tree)) != NULL) {
        quicksort(vec, 0, vec->size - 1, (int (*)(void*, void*)) cmpkey);
        vec_print(vec);
    }

    vec_free(vec);
    tree_free(tree);
    return 0;
}

Key*
key_new(char* value)
{
    Key* key = (Key*) malloc(sizeof(Key));
    assert(key != NULL);
    key->value = strdup(value);
    key->count = 1;
    return key;
}

Tree*
tree_new(void)
{
    Tree* tree = (Tree*) malloc(sizeof(Tree));
    assert(tree != NULL);
    tree->root          = NULL;
    tree->count         = 0;
    tree->inserted_flag = 1;
    return tree;
}

void
tree_free(Tree* tree)
{
    assert(tree != NULL);
    treenode_freeall(tree->root);
    tree->count         = 0;
    tree->inserted_flag = 0;
    free(tree);
}

Vector*
tree_into_refvec(Tree* tree)
{
    assert(tree != NULL);

    if(tree->count == 0) {
        return NULL;
    }

    Key** ptr = (Key**) malloc(tree->count * sizeof(Key*));
    assert(ptr != NULL);

    Vector* vec = vec_new((void**) ptr, tree->count);
    assert(vec != NULL);

    treenode_into_refvec(vec, tree->root);

    vec->ptr = (void**) ptr;
    return vec;
}

Tree*
tree_insert(Tree* tree, char* value, int (*cmp)(void*, void*))
{
    if(tree == NULL && (tree = tree_new()) == NULL) {
        return NULL;
    }
    tree->root = treenode_insert(tree, tree->root, value, cmp);
    if(tree->inserted_flag) {
        tree->inserted_flag = 0;
        tree->count++;
    }
    assert(tree->root != NULL);
    return tree;
}

Treenode*
treenode_insert(Tree*     tree,
                Treenode* root,
                char*     value,
                int (*cmp)(void*, void*))
{
    int comparison;

    if(root == NULL) {
        root = (Treenode*) malloc(sizeof(Treenode));
        assert(root != NULL);
        root->key           = key_new(value);
        root->left          = NULL;
        root->right         = NULL;
        tree->inserted_flag = 1;
    } else if((comparison = cmp(root->key->value, value)) == 0) {
        root->key->count++;
    } else if(comparison > 0) {
        root->left = treenode_insert(tree, root->left, value, cmp);
    } else {
        root->right = treenode_insert(tree, root->right, value, cmp);
    }

    return root;
}

void
treenode_into_refvec(Vector* vec, Treenode* root)
{
    if(root != NULL) {
        treenode_into_refvec(vec, root->left);
        *vec->ptr = root->key;
        vec->ptr++;
        treenode_into_refvec(vec, root->right);
    }
}

void
treenode_freeall(Treenode* root)
{
    if(root != NULL) {
        treenode_freeall(root->left);
        treenode_freeall(root->right);
        treenode_free(root);
    }
}

void
treenode_free(Treenode* root)
{
    assert(root != NULL);
    free(root->key->value);
    root->key->count = 0;
    free(root->key);
    root->left  = NULL;
    root->right = NULL;
    free(root);
}

Vector*
vec_new(void** ptr, unsigned int size)
{
    Vector* vec = (Vector*) malloc(sizeof(Vector));
    if(vec != NULL) {
        vec->ptr  = ptr;
        vec->size = size;
    }
    return vec;
}

void
vec_free(Vector* vec)
{
    assert(vec != NULL);
    free(vec->ptr);
    vec->ptr  = NULL;
    vec->size = 0;
    free(vec);
}

void
swap(Vector* vec, unsigned int idx, unsigned int idy)
{
    void* temp    = vec->ptr[idx];
    vec->ptr[idx] = vec->ptr[idy];
    vec->ptr[idy] = temp;
}

void
quicksort(Vector* vec, int start, int end, int (*cmp)(void*, void*))
{
    int pivot;

    if(start < end) {
        pivot = qs_partition(vec, start, end, cmp);
        quicksort(vec, start, pivot - 1, cmp);
        quicksort(vec, pivot + 1, end, cmp);
    }
    return;
}

int
qs_partition(Vector* vec, int start, int end, int (*cmp)(void*, void*))
{
    int i, last;
    int pivot = end;

    swap(vec, end, (end + start) / 2);
    for(i = last = start; i < pivot; i++) {
        if(cmpkey((Key*) vec->ptr[i], (Key*) vec->ptr[pivot]) < 0) {
            swap(vec, i, last++);
        }
    }
    swap(vec, pivot, last);
    return last;
}

int
cmpkey(Key* keyA, Key* keyB)
{
    return keyA->count - keyB->count;
}

int
getch(void)
{
    if(!empty) {
        empty = 1;
        return chbuff;
    }
    return getchar();
}

void
ungetch(char c)
{
    empty  = 0;
    chbuff = c;
}

int
getword(char* word, unsigned int size)
{
    int   c;
    char* str = word;

    *str = '\0';

    while(isspace((c = getch()))) {
        ;
    }
    if(c != EOF) {
        *str++ = c;
    }
    if(!isalpha(c) && c != '_') {
        *str = '\0';
        return c;
    }
    for(; --size; str++) {
        if(!isalnum(*str = getch())) {
            ungetch(*str);
            break;
        }
    }
    *str = '\0';
    return word[0];
}

void
vec_print(Vector* vec)
{
    unsigned int size = vec->size;
    void**       temp = vec->ptr;

    for(size = vec->size; size--; temp++) {
        printf("%10s %5d\n", ((Key*) *temp)->value, ((Key*) *temp)->count);
    }
}
