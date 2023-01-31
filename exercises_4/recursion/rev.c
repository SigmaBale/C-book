void rev(char s[], int start, int end)
{
    char c;
    c = s[start], s[start] = s[end], s[end] = c;
    if (start < end)
        rev(s, start+1, end-1);
    return;
}