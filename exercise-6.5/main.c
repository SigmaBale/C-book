#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101
#define WORDSIZE   100

typedef struct list {
    struct list* next;
    char*        name;
    char*        replacement;
} list;

list* hashtab[TABLE_SIZE];

unsigned int hash(char*);
list*        lookup(char*);
list*        install(char*, char*);
bool         undef(char*);

unsigned int
hash(char* name)
{
    unsigned int hashvalue;

    for(hashvalue = 0; *name; name++) {
        hashvalue = *name + 31 * hashvalue;
    }
    return hashvalue;
}

list*
lookup(char* name)
{
    list* head;
    for(head = hashtab[hash(name)]; head != NULL; head = head->next) {
        if(strcmp(head->name, name) == 0) {
            return head;
        }
    }
    return NULL;
}

list*
getprev(list* node)
{
    list* head;
    for(head = hashtab[(hash(node->name))]; node != NULL; head = head->next) {
        if(head->next != NULL && strcmp(head->next->name, node->name) == 0) {
            return head;
        }
    }
    return NULL;
}

list*
install(char* name, char* replacement)
{
    list*        head;
    unsigned int hashval;

    if((head = lookup(name)) == NULL) {
        head = (list*) malloc(sizeof(*head));
        if(head == NULL || (head->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        if(hashtab[hashval] == NULL) {
            head->next       = NULL;
            hashtab[hashval] = head;
        } else {
            head->next       = hashtab[hashval];
            hashtab[hashval] = head;
        }
    } else {
        free((void*) head->replacement);
    }
    if((head->replacement = strdup(replacement)) == NULL) {
        return NULL;
    }
    return head;
}

bool
undef(char* name)
{
    list *       head, *prev;
    unsigned int hashval;

    if((head = lookup(name)) != NULL) {
        prev = getprev(head);
        if(prev != NULL) {
            prev->next = head->next;
        } else {
            hashval = hash(name);
            if(head->next != NULL) {
                hashtab[hashval] = head->next;
            } else {
                hashtab[hashval] = NULL;
            }
        }
        free(head->name);
        free(head->replacement);
        free(head);
        return true;
    }
    return false;
}
