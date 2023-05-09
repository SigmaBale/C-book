#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "treenode.h"
#define MAXSIZE             1000
#define DEFAULT_PREFIX_LEN  6
int getl(char *);

int main(int argc, char *argv[]) {
    char *p;
    char word[MAXSIZE];
    int len = DEFAULT_PREFIX_LEN;
    int slen;
    int i, cmp;

    struct linkedlist list = { 0, NULL, NULL };
    struct node *curr_node;
    slen = 0;

next_arg:
    while(--argc && *(++argv)[0] == '-') {
        p = argv[1];
        while (*p) {
            switch (*p) {
                case 'l':
                    if (slen) {
                        printf("Already provided the len\n");
                        return 1;
                    }
                    slen = 1;
                    if (*(p++) == '\0' && --argc)
                        p = *++argv;
                    if ((len = getl(p)) < 0) {
                        printf("Invalid length provided\n");
                        return 1;
                    }
                    goto next_arg;
                    break;
                default:
                    printf("Invalid argument\n");
                    return 1;
                    break;
            }
            p++;
        }
    }

    while (getword(word, MAXSIZE) != EOF) {
        if (isalpha(word[0]) && strlen(word) >= len) {
            for (curr_node = list.head; curr_node != NULL; curr_node = curr_node->next) {
                if (strprefix(curr_node->group->word, word, len) == 0) {
                    curr_node->group = addword(curr_node->group, word);
                    break;
                }
            }
            if (curr_node == NULL) {
                add_node(&list);
                list.tail->group = addword(list.tail->group, word);
            }
        }
    }

    for (curr_node = list.head; curr_node != NULL; curr_node = curr_node->next)
        if (curr_node->group->left != NULL || curr_node->group->right != NULL)
            printtree(curr_node->group);

    return 0;
}

int getl(char *s) {
    int num;

    for (num = 0; isdigit(*s); s++)
        num = num * 10 + (*s - '0');
    if (*s != '\0')
        return -1;
    return num;
}
