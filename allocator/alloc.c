#define BUFFSIZE 10000

static char allocbuf[BUFFSIZE];
static char *allocp = allocbuf;

char *alloc(unsigned int allocation) {
    if(allocation <= allocbuf + BUFFSIZE - allocp) {
        allocp += allocation;
        return allocp - allocation;
    }
    return 0;
}

void afree(char *p) {
    if(p >= allocbuf && p <= allocbuf + BUFFSIZE)
        allocp = p;
    return;
}