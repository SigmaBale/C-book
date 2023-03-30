#include "expand.h"
#include <stdio.h>
#define UNINITIALIZED -1
/*
    -t, --tabs=LIST
        use comma separated list of tab positions.
        The last specified position can be prefixed with '/'
        to specify a tab size to use after the last
        explicitly specified tab stop.  Also a prefix of '+'
        can be used to align remaining tab stops relative to
        the last specified tab stop instead of the first column
*/
static int parse_tablist(int *tablist, char *arg, int size, int *specifier) {
    int prev;
    int num;
    int len;
    int spec;
    int last;
    int c;

    num = spec = last = len = 0;
    /* Skips preceeding whitespaces */
    while (*arg == ' ')
        arg++;
    while (--size > 0 && (c = *++arg) != '\0') {
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
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_NOT_LAST_VALUE, *specifier);
                    return 0;
                }
                if (num == UNINITIALIZED)
                    num = 0;
                num = num * 10 + (c - 48);
                if (spec)
                    *specifier += num;
            case ',':
                if (num != UNINITIALIZED && !spec) {
                    if (num > prev) {
                        *(tablist++) = num;
                        len++;
                    } else {
                        fprintf(stderr, DETAB_ERROR_TAB_SIZE_NOT_ASCENDING);
                        return 0;
                    }
                }
                if (spec)
                    last = 1;
                num = UNINITIALIZED;
                break;
            case '/':
            case '+':
                if (*specifier != c && last) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_MUTUALLY_EXCLUSIVE);
                    return 0;
                }
                if (*specifier || last) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_NOT_LAST_VALUE, *specifier);
                    return 0;
                }
                if (num != UNINITIALIZED) {
                    fprintf(stderr, DETAB_ERROR_SPECIFIER_NOT_AT_START_OF_NUM, c, arg);
                    return 0;
                }
                *specifier = spec = c;
                break;
            default:
                fprintf(stderr, DETAB_ERROR_TAB_SIZE_INVALID_CHAR, arg);
                return 0;
        }
    }
    if (len == 0) {
        fprintf(stderr, DETAB_ERROR_OPTION_REQUIRES_ARGUMENT);
        return 0;
    }
    return len;
}

#define USAGE "USAGE: [detab] [OPTIONS: -t -i] [FILE]\n"

int parse_args(int argc, char *argv[], int *tablist, int *len, int *specifier, int *preceeding) {
    int c;
    while (--argc > 0 && *(++argv)[0] == '-') {
        while ((c = *++argv[0]) != '\0') {
            switch (c) {
                case 't':
                    *len += parse_tablist(tablist + *len, &**argv, TABLIST_SIZE, specifier);
                    if (len == 0)
                        return 1;
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
    return 1;
}
