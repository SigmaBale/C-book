struct treenode {
    char*         word;
    unsigned int        count;
    struct treenode*    left;
    struct treenode*    right;
};

int getword(char *, int);
char *sdup(const char *);
void printree(struct treenode *);
struct treenode *palloc(void);
struct treenode *addtree(struct treenode *, const char *);
