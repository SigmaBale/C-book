int strprefix(char *src, char *dst, unsigned int len) {
    for (int count = 0; count < len; count++)
        if (*src++ != *dst++)
            return -1;
    return 0;
}
