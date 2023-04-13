#include <stdio.h>

/* ERRORS */
#define DETAB_ERROR_SPECIFIER_NOT_LAST_VALUE "detab: '%c' specifier only allowed with the last value\n"
#define DETAB_ERROR_SPECIFIER_MUTUALLY_EXCLUSIVE "'/' specifier is mutually exclusive with '+'\n"
#define DETAB_ERROR_SPECIFIER_NOT_AT_START_OF_NUM "detab: '%c' specifier not at start of number: '%s'\n"
#define DETAB_ERROR_TAB_SIZE_INVALID_CHAR "detab: tab size contains invalid character(s): '%s'\n"
#define DETAB_ERROR_TAB_SIZE_IS_ZERO "detab: tab size cannot be 0\n"
#define DETAB_ERROR_TAB_SIZE_NOT_ASCENDING "detab: tab sizes must be ascending\n"
#define DETAB_ERROR_OPTION_REQUIRES_ARGUMENT "detab: option requires an argument -- t\n"
#define DETAB_ERROR_UNKNOWN_OPTION "detab: unknown option -- '%c'\n"

/* USAGE */
#define USAGE "USAGE: [detab] [OPTIONS: -t -i] [FILE]\n"

#define TABLIST_SIZE 10000

typedef struct {
    int sign;
    int value;
} specifier;

int parse_args(int argc, char *argv[], int *tablist, specifier *s, int *preceeding);
int expand_tab(int tabstop, int idx, char *out);  
int get_tabstop(int *k, int j, int len, int *tablist, int *tabstop);
