#ifndef LIMIT
#define LIMIT       1000    /* Maximum len (in bytes) of a single line */
#endif
#define NUMBER      '0'     /* Signal that indicates the value is a number */
#define NAME        'n'     /* Signal that indicates the value is a name */
#define VARIABLE    'v'     /* Signal that indicates the value is a variable */

extern char buffer[];
extern int buffer_i;
extern double vars[];

int getline(char s[], int limit);
int getop(char s[]);
double pop(void);
void push(double f);
void printop(void);
void dupe(void);
void swap(void);
void clear(void);
void getvar(char s[]);
void mathf(char s[]);