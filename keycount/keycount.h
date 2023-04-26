struct key {
    const char*     word;
    unsigned int    count;
};

enum { OUT, STRCONST, HYPHEN, STAR, COMMENT, PREPROC };
extern int state;

int binsearch(char *, struct key *, int);
int getword(char *, int);
