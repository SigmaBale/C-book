int strend(char *a, char *b) {
    if(*b == '\0')
        return 1;
    char *end = b - 1;
    while(*a != '\0')
        a++;
    while(*b != '\0')
        b++;
    while(b != end)
        if(*b-- != *a--)
            return 0;
    return 1;
}