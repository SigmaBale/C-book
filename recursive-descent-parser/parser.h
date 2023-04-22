#define MAXTOKEN 100

enum inputtype { PARANS, BRACKETS, NAME, QUALIFIER, DATATYPE };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int getch(void);
void ungetch(int ch);

extern int tokentype;
extern int err;
extern char token[MAXTOKEN];
extern char name[MAXTOKEN];
extern char out[1000];
extern char qualifier[MAXTOKEN];
extern char returntype[MAXTOKEN];
