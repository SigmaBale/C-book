#include<stdio.h>
#define SPACE       8    /* Tab space for entab, detab functions */
#define MAXLINE 10000    /* Max size of char array */
#define LINE       20    /* Max chars per line for fold function */

#define END         1    /* State - currently at closing char '/' of comment */
#define INSIDE      2    /* State - currently inside a comment body */
#define OUTSIDE     3    /* State - outside of comment and quotes */
#define INQUOTES    4    /* State - inside quotes */

#define OPENING     5    
#define CLOSING     6
#define NONE        7

int get_line(char s[]);
int get_raw_text(char s[]);
int detab(char s[], char new[]);
int entab(char s[], char new[]);
int get_tab_stop(int start);
void fold(char s[], char new[]);
void rem_comments(char s[], char new[]);
int get_state(char s[], int i, int state);
void log_syntax(char s[]);
int type(char c);
int opposite(char c);

int main()
{
    int len, nlen;
    char buffer[MAXLINE];                   /* Buffer for getline */
    char new[MAXLINE];                      /* Second buffer for buffer manipulation */

    while((len = get_raw_text(buffer)) > 0) {
        log_syntax(buffer);
    }
    return 0;
}

int entab(char s[], char new[])
{
    int i, k, len, end, tab_stop;

    i = k = 0;
    while((new[i] = s[k]) != '\0') {
        if (new[i] == ' ') {
            for(len = 0; s[k + len] == ' '; ++len)
                ;
            end = k + len - 1;
            tab_stop = get_tab_stop(k);
            while(end >= tab_stop - 1) {
                if (k == tab_stop - 1)
                    new[i] = ' ';
                else 
                    new[i] = '\t';
                k = tab_stop;
                tab_stop = get_tab_stop(tab_stop);
                ++i;
            }
            while(k <= end) {
                new[i] = ' ';
                ++i;
                ++k;
            }
        }
        else {
            ++i;
            ++k;
        } 
    }
    return i;
}

int detab(char s[], char new[])
{
    int i, j, k;

    i = k = 0;
    while((new[i] = s[k]) != '\0') {
        if(new[i] == '\t') {
            for(j = i; j < ((i + SPACE) / SPACE * SPACE); ++j)
                new[j] = ' ';
            i = j-1;
        }
        ++i;
        ++k;
    }
    return i;
}

int get_line(char buffer[])
{
    int i, c;

    i = 0;
    while((c = getchar()) != EOF && i < (MAXLINE-1) && c != '\n') {
        buffer[i] = c;
        ++i;
    }
    if (c == '\n') {
        buffer[i] = '\n';
        ++i;
    }
    buffer[i] = '\0';
    return i;
}

int get_raw_text(char buffer[])
{
    int i, c;

    i = 0;
    while((c = getchar()) != EOF && i < MAXLINE) {
        buffer[i] = c;
        ++i;
    }
    buffer[i] = '\0';
    return i;
}

int get_tab_stop(int start)
{
    return ((start + SPACE) / SPACE * SPACE);
}

void fold(char buffer[], char new[])
{
    int i, j, k;

    k = 1;
    i = j = 0;
    while((new[i] = buffer[j]) != '\0') {
        if (new[i] == '\t')
            k += SPACE;
        if (k >= LINE - 1) {
            ++i;
            while((buffer[j] == ' ' || buffer[j] == '\t') && buffer[j] != '\0') {
                if (buffer[j] == '\0') {
                    new[i] = '\n';
                    return;
                }
                ++j;
            }
            new[i] = '\n';
            ++i;
            k = 1;
        }
        else {
            ++i;
            ++j;
            ++k;
        }
    }
}

void rem_comments(char buffer[], char new[])
{
    int i, j, state;

    i = j = 0;
    state = get_state(buffer, j, OUTSIDE);
    while((new[i] = buffer[j]) != '\0') {
        if (state != OUTSIDE && state != INQUOTES)
            while (state != OUTSIDE && state != INQUOTES) {    
                ++j;
                state = get_state(buffer, j, state);
            }
        else {
            ++j;
            ++i;
            state = get_state(buffer, j, state);
        }
    }
}

int get_state(char buffer[], int i, int state)
{
    if (i == 0 && buffer[i] == '/' && buffer[i+1] == '*' && state == OUTSIDE) {
        return INSIDE;
    } else if (i > 0) {
        if(buffer[i-1] != '\\' && buffer[i] == '\'' && state == OUTSIDE)
            return INQUOTES;
        if(buffer[i-1] != '\\' && buffer[i] == '"' && state == OUTSIDE)
            return INQUOTES;
        if(buffer[i-1] != '\\' && buffer[i] == '\'' && state == INQUOTES)
            return OUTSIDE;
        if(buffer[i-1] != '\\' && buffer[i] == '"' && state == INQUOTES)
            return OUTSIDE;
        if(buffer[i] == '/' && buffer[i+1] == '*' && state == OUTSIDE)
            return INSIDE;
        if(buffer[i-1] == '*' && buffer[i] == '/' && state == INSIDE)
            return END;
        if(state == END)
            return OUTSIDE;
    }
    return state;
}

void syntax_error(char c1, char c2, int line, int column);

void log_syntax(char buffer[])
{
    int i, j, c;
    int state, t;
    int line, col;
    char stack[MAXLINE];

    line = 1;
    i = j = col = 0;
    state = get_state(buffer, i, OUTSIDE);
    while((c = buffer[i]) != '\0') {
        if (c == '\n') {
            ++line;
            col = 0;
        }
        else if (state == OUTSIDE && (t = type(c)) != NONE) {
            if (t == OPENING) {
                stack[j] = opposite(c);
                ++j;
            }
            else {
                if (j == 0)
                    syntax_error(c, 0, line, col);
                else {
                    j--;
                    if (stack[j] != c)
                        syntax_error(opposite(stack[j]), c, line, col);
                }
            }
        }
        ++col;
        ++i;
        state = get_state(buffer, i, state);
    }
}

int type(char c) 
{
    if (c == '(' || c == '[' || c == '{')
        return OPENING;
    if (c == ')' || c == ']' || c == '}')
        return CLOSING;
    return NONE;
}

void syntax_error(char c1, char c2, int line, int column)
{
    if (c2 == 0)
        printf("Syntax Error: unmatched '%c' in line %d column %d\n", c1, line, column);
    else
        printf("Syntax Error: unmatched '%c' just before '%c' in line %d column %d\n", c1, c2, line, column);
}

int opposite(char c)
{
    if (c == ')')
        return '(';
    if (c == ']')
        return '[';
    if (c == '}')
        return '{';
    if (c == '(')
        return ')';
    if (c == '[')
        return ']';
    else
        return '}';
}