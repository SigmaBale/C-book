#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSIZE   sizeof(noise) / sizeof(noise[0])
#define MAXWORD (size_t) 1000
char ch;
int  empty = 1;

struct Listnode {
    unsigned int     line;
    struct Listnode* next;
};

struct Treenode {
    char*              word;
    struct Linkedlist* lines_list;
    struct Treenode*   right;
    struct Treenode*   left;
};

struct Linkedlist {
    struct Listnode* head;
    struct Listnode* tail;
};

struct Treenode*   treenode_insert(struct Treenode*, char*, unsigned int);
struct Linkedlist* new_list(void);
int                getch(void);
void               ungetch(char);
int                is_contained_in(const char*, const char**, size_t size);
int                getword(char*, size_t);
int                quicksort(unsigned int start, unsigned int end);
void               list_insert(struct Linkedlist*, unsigned int);
void               print_tree(struct Treenode*);
void               print_list(struct Listnode*);

int main() {
    int                lnum;
    char               word[MAXWORD];
    static const char* noise[] = { "the", "and", "it", "on" };
    struct Treenode*   words = NULL;

    lnum = 0;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !is_contained_in(word, noise, NSIZE))
            words = treenode_insert(words, word, lnum);
        if (word[0] == '\n')
            lnum++;
    }

    printf("\n");
    print_tree(words);

    return 0;
}

int getch(void) {
    if (empty)
        return getchar();
    else {
        empty = 1;
        return ch;
    }
}

void ungetch(char c) {
    empty = 0;
    ch = c;
}

int is_contained_in(const char* word, const char* list[], size_t size) {
    for (; --size; list++)
        if (strcmp(word, *list) == 0)
            return 1;
    return 0;
}

int getword(char* word, size_t len) {
    int   c;
    char* str = word;

    while ((c = getch()) != '\n' && isspace(c))
        ;
    if (c != EOF)
        *str++ = c;
    if (!isalpha(c)) {
        *str = '\0';
        return c;
    }
    for (; --len; str++)
        if (!isalnum(*str = getch())) {
            ungetch(*str);
            break;
        }
    *str = '\0';
    return word[0];
}

void list_insert(struct Linkedlist* list, unsigned int line) {
    unsigned int prevline;

    if (list->tail != NULL && list->tail->line == line)
        return;
    else {
        struct Listnode* new_node = (struct Listnode*) malloc(sizeof(struct Listnode));
        new_node->next = NULL;
        new_node->line = line;

        if (list->tail == NULL) {
            list->head = new_node;
        } else if ((prevline = list->tail->line) < line) {
            list->tail->next = new_node;
        } else if (prevline > line) {
            printf("Error, line is less than the previous line\n");
            return;
        }
        list->tail = new_node;
    }
}

struct Linkedlist*
new_list(void) {
    struct Linkedlist* list = (struct Linkedlist*) malloc(sizeof(struct Linkedlist));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

struct Treenode*
treenode_insert(struct Treenode* root, char* word, unsigned int line) {
    int comparison;

    if (root == NULL) {
        root = (struct Treenode*) malloc(sizeof(struct Treenode));
        root->word = strdup(word);
        root->lines_list = new_list();
        list_insert(root->lines_list, line);
        root->right = NULL;
        root->left = NULL;
    } else if ((comparison = strcmp(root->word, word)) == 0)
        list_insert(root->lines_list, line);
    else if (comparison > 0)
        root->left = treenode_insert(root->left, word, line);
    else if (comparison < 0)
        root->right = treenode_insert(root->right, word, line);
    return root;
}

void print_tree(struct Treenode* tree) {
    if (tree != NULL) {
        print_tree(tree->left);
        printf("%15s ", tree->word);
        print_list(tree->lines_list->head);
        print_tree(tree->right);
    }
}

void print_list(struct Listnode* node) {
    if (node != NULL) {
        printf(" %4u", node->line);
        print_list(node->next);
    } else
        printf("\n");
}
