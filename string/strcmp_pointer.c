int strcmp(char *a, char *b) {
    for(; *a == *b; a++, b++)
        if(*a == '\0')
            return 0;
    return *a - *b;
}