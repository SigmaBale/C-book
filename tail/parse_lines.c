#include <ctype.h>

int parse_lines(char *str, int *lines) {
    int c;
    int num;
    int invalid;

    invalid = 1;
    while(isdigit(c = *str++) && c != '\0') {
        if (invalid)
            num = 0, invalid = 0;
        num = num * 10 + (c - '0');
    }

    if(c != '\0' || invalid)
        return -1;

    *lines = num;

    return 0;
}
