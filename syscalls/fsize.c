#include <dirent.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PRINT_SIZE(size, name) fprintf(stdout, "%8ld %s\n", (size), name)

void error(char* fmt, ...);
void fsize(char* name);
void dirwalk(char* dir, void (*fn)(char*));

int
main(int argc, char* argv[])
{
    if(argc == 1)
        fsize(".");
    else
        while(--argc)
            fsize(*++argv);

    return 0;
}

void
fsize(char* name)
{
    struct stat statbuf;
    uint        mask;

    if(stat(name, &statbuf) == -1) {
        fprintf(stderr, "error getting attributes for '%s'", name);
        return;
    }

    if((mask = (statbuf.st_mode & S_IFMT)) == S_IFREG || mask == S_IFLNK)
        PRINT_SIZE(statbuf.st_size, name);
    else if(mask == S_IFDIR)
        dirwalk(name, fsize);
}

void
dirwalk(char* dir, void (*fn)(char*))
{
    DIR*           dirp;
    struct dirent* entry;
    char*          ename;
    char           name[FILENAME_MAX];

    if((dirp = opendir(dir)) == NULL) {
        fprintf(stderr, "can't open dir '%s'", dir);
        return;
    }

    while((entry = readdir(dirp)) != NULL) {
        if(strcmp((ename = entry->d_name), ".") == 0 || strcmp(ename, "..") == 0)
            continue;
        if(strlen(dir) + strlen(ename) + 2 >= FILENAME_MAX) {
            fprintf(stderr, "file path too large for '%s'\n", ename);
            return;
        } else {
            sprintf(name, "%s/%s", dir, ename);
            (*fn)(name);
        }
    }

    closedir(dirp);
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
    exit(1);
}
