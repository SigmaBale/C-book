#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE   1000
#define PAGE_SIZE 40

typedef struct {
    unsigned int line;
    unsigned int pagenr;
} Page;

typedef struct {
    Page* page;
    char* title;
    FILE* fp;
} File;

Page* page_new(void);
File* file_new(FILE*, char*);
void  file_free(File*);
int   file_print_pages(File*);
void  file_print_title(File*);
void  file_print_pagenr(File*);

int
main(int argc, char* argv[])
{
    FILE* fp;
    char *title, *prog;
    File* file;

    prog = argv[0];

    if(argc == 1) {
        fprintf(stderr, "usage: %s [file1 file2...]\n", prog);
        exit(1);
    } else {
        while(--argc) {
            if((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s", prog, *argv);
                exit(2);
            } else {
                if((file = file_new(fp, *argv)) == NULL) {
                    fprintf(stderr, "%s: couldn't create a file\n", prog);
                    exit(5);
                }
                switch(file_print_pages(file)) {
                    case 1:
                        fprintf(stderr, "%s: error while writing to stdout\n", prog);
                        exit(3);
                    case 2:
                        fprintf(stderr, "%s: error while reading file %s\n", prog, *argv);
                        exit(4);
                    default:
                        file_free(file);
                        fclose(fp);
                        break;
                }
            }
        }
    }
    exit(0);
}

Page*
page_new(void)
{
    Page* page = (Page*) malloc(sizeof(Page));
    if(page != NULL) {
        page->line   = 1;
        page->pagenr = 1;
    }
    return page;
}

File*
file_new(FILE* fp, char* title)
{
    if(fp == NULL || title == NULL)
        return NULL;
    File* file = (File*) malloc(sizeof(File));
    if(file != NULL) {
        file->fp    = fp;
        file->title = strdup(title);
        if((file->page = page_new()) == NULL) {
            free(file->page);
            free(file);
            return NULL;
        }
    }
    return file;
}

int
file_print_pages(File* file)
{
    char buf[MAXLINE];

    if(file != NULL) {
        fprintf(stdout, "Title: %s\n", file->title);
        while(fgets(buf, MAXLINE, file->fp) != NULL) {
            fprintf(stdout, "%s", buf);
            if(file->page->line++ >= PAGE_SIZE) {
                file_print_pagenr(file);
                fprintf(stdout, "\n");
                file->page->pagenr++;
                file->page->line = 1;
                file_print_title(file);
            }
        }
        if(ferror(stdout))
            return 1;
        else if(ferror(file->fp))
            return 2;
        fprintf(stdout, "\n");
        file_print_pagenr(file);
    }
    return 0;
}

void
file_print_title(File* file)
{
    if(file != NULL)
        fprintf(stdout, "Title -> %s\n", file->title);
}

void
file_print_pagenr(File* file)
{
    if(file != NULL)
        fprintf(stdout, "Page -> %u\n", file->page->pagenr);
}

void
file_free(File* file)
{
    if(file != NULL) {
        free(file->title);
        free(file->page);

        file->title = NULL;
        file->fp    = NULL;
        file->page  = NULL;
        free(file);
    }
}
