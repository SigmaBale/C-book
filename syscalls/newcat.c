#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void error(char* fmt, ...);

int
main(int argc, char* argv[])
{
    int         fd, n;
    time_t      tic, toc, start, end;
    long double elapsed;
    char*       prog = argv[0];
    char        buf[BUFSIZ];
    char*       bufp = buf;

    start = clock();
    if(__builtin_expect(argc == 1, 0)) {
        // You can't benchmark this...
        while((n = read(0, buf, BUFSIZ)) > 0) {
            bufp = buf;
            if(write(1, bufp, n) != n)
                error("write error on file '%s'", stdout);
        }
    } else {
        while(--argc) {
            tic = clock();
            fd  = open(*++argv, O_RDONLY);
            toc = clock();

            elapsed = (double) (toc - tic) / CLOCKS_PER_SEC;
            printf("\nTIME: opening file -> %Lf ms\n", elapsed * 1000);

            if(fd == -1)
                error("cant open '%ls'", *argv);

            tic = clock();

            while((n = read(fd, buf, BUFSIZ)) > 0)
                if(write(1, bufp, n) != n)
                    error("write error on file '%s'", stdout);

            toc     = clock();
            elapsed = (double) (toc - tic) / CLOCKS_PER_SEC;
            printf("\nTIME: reading/writing a file -> %Lf ms\n", elapsed * 1000);

            tic = clock();
            close(fd);
            toc     = clock();
            elapsed = (double) (toc - tic) / CLOCKS_PER_SEC;
            printf("\nTIME: closing a file -> %Lf ms\n", elapsed * 1000);
        }
    }
    end     = clock();
    elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    printf("\nTIME: program end -> %Lf ms\n", elapsed * 1000);

    return 0;
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
