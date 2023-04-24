#include <string.h>
#include "keycount.h"

int binsearch(char *src, struct key *dest, int limit) {
    int low, high, mid;
    int result;

    low = 0;
    high = limit-1;
    while (low <= high) {
        mid = (high+low)/2;
        if ((result = strcmp(src, dest[mid].word)) < 0)
            high = mid - 1;
        else if (result > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
