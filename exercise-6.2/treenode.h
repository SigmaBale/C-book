struct linkedlist {
    unsigned int    len;
    struct node *head;
    struct node *tail;
};

struct node {
    struct treenode *group;
    struct node *next;
};

struct treenode {
    char* word;
    struct treenode* left;
    struct treenode* right;
};

enum state { OUT, SLASH, STAR, COMMENT, STRLIT, PREPROC };
enum type { NONE, CHAR, INT, FLOAT, DOUBLE, LONG };

struct node *nalloc(void);
struct node *add_node(struct linkedlist *);
struct treenode* talloc(void);
struct treenode* addword(struct treenode *, char *);

char* sdup(char *);
int strprefix(char *, char *, unsigned int);
int getword(char *, unsigned int);
void printtree(struct treenode *);
