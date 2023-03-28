/*
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
*/