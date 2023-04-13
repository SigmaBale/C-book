#include "expand.h"
#include <ctype.h>
#include <stdio.h>
size_t maxline = 1000;
#define MAXLINE maxline
#define MAXSIZE 10000

int main(int argc, char *argv[]) {
    /* Input buffer and parsed output buffer */
    char text[MAXLINE];
    char *buffer = text;
    char out[MAXSIZE];
    /* Tabstops values and len of tablist */
    int tablist[TABLIST_SIZE];
    int tabstop;
    int last_tab;
    int len;
    /* Char holder and counters */
    int c, i, j, k;
    /* Flags: option and logic flag */
    int preceeding;
    int abs_flag;
    /* Specifier + or / with value */
    specifier s = {0, 0};
    /* Default tabstop value */
    tabstop = 8;

    preceeding = len = 0;
    if ((len = parse_args(argc, argv, tablist, &s, &preceeding)) < 0)
        return 1;

    last_tab = (len) ? tablist[len-1] : -1;

    for(k = 0; getline(&buffer, &MAXLINE, stdin) > 0; k = 0) {
        for (i = j = 0; (c = text[i]); i++) {
            if(preceeding && !isblank(c)) {
                /* Copy the rest of the input */
                while ((out[j++] = text[i++]))
                    ;
                break;
            }
            if (c == '\t') {
                if (get_tabstop(&k, j, len, tablist, &tabstop) == 0)
                    ;
                else if(s.sign) {
                    if (s.sign == '/') {
                        abs_flag = 1;
                        tabstop = s.value;
                    }
                    else {
                        if (last_tab > tabstop)
                            tabstop = last_tab;
                        while((tabstop += s.value) < j)
                            ;
                    }
                }
                else if (len == 1 || len == 0)
                    abs_flag = 1;
                else {
                    out[j++] = ' ';
                    continue;
                }
                j = expand_tab(tabstop, j, out);
            }
            else
                out[j++] = c;
        }
        printf("%s\n", out);
    }
    return 0;
}
