#include <stdio.h>
#include <stdlib.h>

void fcopy(FILE*, FILE*);

int
main(int argc, char* argv[])
{
    FILE* fp;
    char* prog = argv[0];

    if(argc == 1) {
        fcopy(stdin, stdout);
    } else {
        while(--argc) {
            if((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open '%s'\n", prog, *argv);
                exit(1);
            } else {
                fcopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    if(ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

void
fcopy(FILE* input_filep, FILE* output_filep)
{
    int c;
    while((c = getc(input_filep)) != EOF)
        putc(c, output_filep);
}
