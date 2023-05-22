#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

char* fpattern(char*, char*, FILE*, char*);
int   fgetline(char*, unsigned int, FILE*);
int   strncompare(const char*, const char*, size_t);
char* strchar(register const char*, int);
char* strstr(const char*, const char*);

int
main(int argc, char* argv[])
{
    char* prog = argv[0];
    char* pattern;
    FILE* streamp = NULL;
    char  buf[MAXLINE];

    if(argc < 2) {
        fprintf(stderr, "%s: usage <pattern> [file1 file2...]\n", prog);
        exit(1);
    } else {
        pattern = *++argv;
        if(argc-- == 2)
            streamp = stdin;
        while(--argc || streamp == stdin) {
            if(streamp == stdin || (streamp = fopen(*++argv, "r")) != NULL) {
                while(fgets(buf, MAXLINE, streamp) != NULL) {
                    if(strstr(buf, pattern) != NULL)
                        fprintf(stdout, "%s: %s", (streamp != stdin) ? *argv : "stdin", buf);
                }
                if(ferror(streamp)) {
                    fprintf(stderr, "%s: error while reading %s\n", prog, (streamp != stdin) ? *argv : "stdin");
                    exit(3);
                } else if(ferror(stdout)) {
                    fprintf(stderr, "%s: error while writing to stdout\n", prog);
                    exit(4);
                }
                fclose(streamp);
                if(streamp == stdin)
                    break;
            } else if(streamp == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(2);
            }
        }
    }
    exit(0);
}

char*
strchar(register const char* s, int a)
{
    do {
        if(*s == a)
            return (char*) s;
    } while(*s++);

    return 0;
}

int
strncompare(const char* s1, const char* s2, size_t len)
{
    // Ensure the signdness
    const unsigned char* p1 = (const unsigned char*) s1;
    const unsigned char* p2 = (const unsigned char*) s2;
    unsigned char        c1, c2;

    while(len-- > 0) {
        c1 = *p1++, c2 = *p2++;
        if(c1 == '\0' || c1 != c2)
            return c1 - c2;
    }

    return c1 - c2;
}

char*
strstr(const char* haystack, const char* needle)
{
    const char*  s1  = haystack;
    const size_t len = strlen(needle);

    for(; strchar(s1, *needle) != 0; s1++)
        if(strncompare(s1, needle, len) == 0)
            return (char*) s1;

    return NULL;
}
