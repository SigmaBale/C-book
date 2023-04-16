#include <stdio.h>
#include "expand.h"
#define UNINITIALIZED -1

static int parse_tablist(int *tablist, char *arg, int size, specifier *s) {
    int prev;
    int num;
    int len;
    int spec;
    int last;
    int c;
    int *sign = &s->sign;
    int *value = &s->value;

    num = prev = UNINITIALIZED;
    spec = last = len = 0;
    while (--size > 0 && (c = *arg++) != '\0') {
        switch (c) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (last) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_NOT_LAST_VALUE, *sign);
                    return -1;
                }
                if (num == UNINITIALIZED)
                    num = 0;
                num = num * 10 + (c - 48);
                if (spec)
                    *value = num;
                break;
            case ',':
                if (num != UNINITIALIZED && !spec) {
                    if (num > prev) {
                        *(tablist++) = num;
                        prev = num;
                        len++;
                    } else {
                        fprintf(stderr, DETAB_ERROR_TAB_SIZE_NOT_ASCENDING);
                        return -1;
                    }
                }
                if (spec)
                    last = 1;
                num = UNINITIALIZED;
                break;
            case '/':
            case '+':
                if (*sign != c && last) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_MUTUALLY_EXCLUSIVE);
                    return -1;
                }
                if (*sign || last) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_NOT_LAST_VALUE, *sign);
                    return -1;
                }
                if (num != UNINITIALIZED) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_NOT_AT_START_OF_NUM, c, arg);
                    return -1;
                }
                *sign = c;
                spec = 1;
                break;
            default:
                fprintf(stderr, DETAB_ERROR_TAB_SIZE_INVALID_CHAR, arg);
                return -1;
        }
    }
    if (len == 0 && !spec) {
        fprintf(stderr, DETAB_ERROR_OPTION_REQUIRES_ARGUMENT);
        return -1;
    }
    return len;
}



int parse_args(int argc, char *argv[], int *tablist, specifier *s, int *preceeding) {
    int c, len;
    char *arg;
next_parameter:
    while (--argc && *(++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch (c) {
                case 't':
                    if (*(*argv+1) == '\0' && argc > 1) {
                        arg = *(++argv);
                        argc--;
                    }
                    else
                        arg = (&**argv)+1;
                    len += parse_tablist(tablist + len, arg, TABLIST_SIZE, s);
                    if (len == -1)
                        return len;
                    /* Can use goto because while loop is not reseting any state */
                    goto next_parameter;
                    break;
                case 'i':
                    *preceeding = 1;
                    break;
                default:
                    fprintf(stderr, DETAB_ERROR_UNKNOWN_OPTION, c);
                    fprintf(stderr, USAGE);
                    return -1;
            }
        }
    }
    return len;
}

int expand_tab(int tabstop, int j, char *out) {
    int k, spaces;

    spaces = tabstop - (j % tabstop);
    for (k = 0; k < spaces || k == 0; k++)
        out[k + j] = ' ';
    return j + spaces;
}

int get_tabstop(int *k, int j, int len, int *tablist, int *tabstop) {
    while(*k < len)
        if((*tabstop = tablist[*k++]) > j)
            return 0;
    return -1;
}
