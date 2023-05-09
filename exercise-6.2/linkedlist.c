#include <stdlib.h>
#include "treenode.h"

struct node *add_node(struct linkedlist *list) {
    struct node *new_node = nalloc();
    struct node *old_tail = list->tail;

    new_node->group = NULL;
    new_node->next = NULL;

    if (old_tail != NULL)
        old_tail->next = new_node;
    else
        list->head = new_node;

    list->tail = new_node;
    list->len++;

    return new_node;
}

struct node *nalloc(void) {
    return (struct node *) malloc(sizeof(struct node));
}
