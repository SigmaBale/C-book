/* ERRORS */
#define DETAB_ERROR_SPECIFIER_NOT_LAST_VALUE "detab: '%c' specifier only allowed with the last value\n"
#define DETAB_ERROR_SPECIFIER_MUTUALLY_EXCLUSIVE "'/' specifier is mutually exclusive with '+'\n"
/* Formats and displays the char array where error occured from specifier symbol in question up to the null terminator */
#define DETAB_ERROR_SPECIFIER_NOT_AT_START_OF_NUM "detab: '%c' specifier not at start of number: '%s'\n"
/* Formats and displays the char array where error occured from invalid character up to the null terminator */
#define DETAB_ERROR_TAB_SIZE_INVALID_CHAR "detab: tab size contains invalid character(s): '%s'\n"
#define DETAB_ERROR_TAB_SIZE_IS_ZERO "detab: tab size cannot be 0\n"
#define DETAB_ERROR_TAB_SIZE_NOT_ASCENDING "detab: tab sizes must be ascending\n"
#define DETAB_ERROR_OPTION_REQUIRES_ARGUMENT "detab: option requires an argument -- t\n"
#define DETAB_ERROR_UNKNOWN_OPTION "entab: unknown option -- '%c'\n"

#define TABLIST_SIZE 10000

int parse_args(int argc, char *argv[], int *tablist, int *len, int *specifier, int *preceeding);
