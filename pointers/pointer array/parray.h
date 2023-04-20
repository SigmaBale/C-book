#define MAXLINE 1000

typedef struct {
    int (*cmp)(void *, void *);
    int reverse;
    int fold;
    int field;
    char delim[MAXLINE];
} flags;

int readlines(char *array[], int lines);
void printarray(char *a[], int len);
void quicksort(void *a[], int start, int end, flags *options);
