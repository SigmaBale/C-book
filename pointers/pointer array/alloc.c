#define BUFSIZE 10000

static char allocbuf[BUFSIZE];
static char *allocp = allocbuf;

char *alloc(int size) {
    if(allocbuf + BUFSIZE - allocp >= size) {
        allocp += size;
        return allocp - size;
    }
    return 0;
}

void afree(char *p) {
    if(p >= allocbuf && p <= allocbuf + BUFSIZE)
        allocp = p;
    return;
}