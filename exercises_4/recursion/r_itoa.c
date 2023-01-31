#include <stdlib.h>
#include <string.h>

void rev(char s[], int start, int end);

static int dtoa(int x, char s[], int s_idx)
{
    s[s_idx++] = abs(x % 10) + '0';
    if ((x /= 10))
        s_idx = dtoa(x, s, s_idx);
    return s_idx;
}

void r_itoa(int x, char s[])
{
    int sign, last;
    if ((sign = x) < 0)
        x = -x;
    last = dtoa(x, s, 0);
    if (sign < 0)
        s[last++] = '-';
    s[last] = '\0';
    rev(s, 0, strlen(s)-1);
    return;
}