void strcpy(char *a, char *b) {
    int i = 0;
    while((a[i] = b[i]) != '\0')
        i++;
}