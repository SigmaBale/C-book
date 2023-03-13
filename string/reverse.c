int strlen(char *p) {
    int i;
    while(*p++)
        i++;
    return i;
}

void strrev(char *p) {
    char *end = p + strlen(p) - 1;
    int temp;

    while(p < end) {
        temp = *p;
        *p++ = *end;
        *end-- = temp;
    }
}