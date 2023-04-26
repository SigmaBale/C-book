#include <string.h>
#include "keycount.h"

struct key *binsearch(char *src, struct key *dest, int limit) {
    int result;
    struct key *low, *high, *mid;

    low = &dest[0];
    high = &dest[limit];
    while (low < high) {
        mid = low + (high - low) / 2;
        if ((result = strcmp(src, mid->word)) < 0)
            high = mid;
        else if (result > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
}
