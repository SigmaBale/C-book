#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void error(char* fmt, ...);
void fcopy(FILE* inp, FILE* out);

int
main(int argc, char* argv[])
{
    FILE*       fp;
    time_t      tic, toc, start, end;
    long double elapsed;
    char*       prog = argv[0];

    start = clock();
    if(__builtin_expect(argc == 1, 0)) {
        // You can't benchmark this...
        fcopy(stdin, stdout);
    } else {
        while(--argc) {
            tic     = clock();
            fp      = fopen(*++argv, "r");
            toc     = clock();
            elapsed = (double) (toc - tic) / CLOCKS_PER_SEC;
            printf("\nTIME: opening file -> %Lf ms\n", elapsed * 1000);

            if(fp == NULL)
                error("can't open '%s'", *argv);

            tic = clock();

            fcopy(fp, stdout);
            if(ferror(stdout))
                error("write error on file '%s'", stdout);

            toc     = clock();
            elapsed = (double) (toc - tic) / CLOCKS_PER_SEC;
            printf("\nTIME: reading/writing a file -> %Lf ms\n", elapsed * 1000);

            tic = clock();
            fclose(fp);
            toc     = clock();
            elapsed = (double) (toc - tic) / CLOCKS_PER_SEC;
            printf("\nTIME: closing a file -> %Lf ms\n", elapsed * 1000);
        }
    }
    end     = clock();
    elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    printf("\nTIME: program end -> %Lf ms\n", elapsed * 1000);
}

void
error(char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "error: ");
    vprintf(fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(EXIT_FAILURE);
}

void
fcopy(FILE* input_filep, FILE* output_filep)
{
    int c;
    while((c = getc(input_filep)) != EOF)
        putc(c, output_filep);
}
