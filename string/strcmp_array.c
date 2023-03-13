int strcmp(char *a, char *b) {
    int i;
    for(i = 0; a[i] == b[i]; i++)
        if(a[i] == '\0')
            return 0;
    return a[i] - b[i];
}