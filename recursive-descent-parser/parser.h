#define MAXTOKEN 100

enum { PARANS, BRACKETS, NAME };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int getch(void);
void ungetch(int ch);

extern int tokentype;
extern char token[MAXTOKEN];
extern char name[MAXTOKEN];
extern char out[1000];
extern char datatype[MAXTOKEN];
