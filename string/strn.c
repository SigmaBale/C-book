void strcpy(char *a, char *b, unsigned int n) {
    while(*a++ = *b++ && n--)
        ;
}

void strcat(char *a, char *b, unsigned int n) {
    while(*a && n--)
        a++;
    while(*a++ = *b++)
        ;
}

int strcmp(char *a, char *b, unsigned int n) {
    for(; *a == *b && n--; a++, b++)
        if(*a == '\0')
            return 0;
    return *a - *b;
}