#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

#ifndef INVALID_FILE_ERR
#define INVALID_FILE_ERR(prog, name) fprintf(stderr, "%s: can't open %s\n", prog, name)
#endif

#ifndef ERROR_READING_FILE
#define ERROR_READING_FILE(prog, name) fprintf(stdout, "%s: error while reading %s\n", prog, name);
#endif

unsigned int getlinel(char*, unsigned int, FILE*);

int
main(int argc, char* argv[])
{
    FILE *file1, *file2;
    char* prog = argv[0];
    char  buf1[MAXLINE], buf2[MAXLINE];

    if(argc != 3) {
        fprintf(stderr, "%s: missing files\n", prog);
        exit(1);
    } else {
        if((file1 = fopen(*++argv, "r")) == NULL || (file2 = fopen(*++argv, "r")) == NULL) {
            INVALID_FILE_ERR(prog, *argv);
            exit(2);
        }
        while(getlinel(buf1, MAXLINE, file1) > 0 && getlinel(buf2, MAXLINE, file2) > 0) {
            if(strcmp(buf1, buf2) != 0) {
                printf("1: %s", buf1);
                printf("2: %s", buf2);
                break;
            }
        }
        if(ferror(file1)) {
            ERROR_READING_FILE(prog, "file_1");
            exit(3);
        } else if(ferror(file2)) {
            ERROR_READING_FILE(prog, "file_2");
            exit(3);
        }
        fclose(file1);
        fclose(file2);
    }
    exit(0);
}

unsigned int
getlinel(char* buff, unsigned int len, FILE* stream)
{
    if((fgets(buff, len, stream) == NULL))
        return 0;
    else
        return strlen(buff);
}
