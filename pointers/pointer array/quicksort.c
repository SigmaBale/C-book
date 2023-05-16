#include "parray.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char* lowerstr(char* p) {
    char* ptr = p;
    while((*ptr = tolower(*ptr)))
        ptr++;
    return p;
}

static char* strfromp(char* start, char* end) {
    char* ptr = start;
    if(start == NULL)
        return NULL;
    if(end == NULL)
        return start;
    while(ptr != end)
        ptr++;
    *ptr = '\0';
    return start;
}

static void swap(void* a[], int src, int dst) {
    void* temp;
    temp   = a[src];
    a[src] = a[dst];
    a[dst] = temp;
}

static int partition(void* a[], int start, int end, flags* options) {
    int pivot, pivot_id, id;
    int comparison;

    pivot    = end;
    pivot_id = start;

    for(id = pivot_id; id < pivot; id++) {
        char idb[MAXLINE];
        strcpy(idb, a[id]);
        char pivotb[MAXLINE];
        strcpy(pivotb, a[pivot]);

        char* idp    = idb;
        char* pivotp = pivotb;
        char* idend;
        char* pivotend;
        int   field;
        int   len = strlen(options->delim);

        if((field = options->field)) {
            while(--field) {
                idp    = strstr(idp, options->delim);
                pivotp = strstr(pivotp, options->delim);
            }

            if(idp == NULL || pivotp == NULL)
                continue;

            idp    += len;
            pivotp += len;

            idend    = strstr(idp, options->delim);
            pivotend = strstr(pivotp, options->delim);

            idp    = strfromp(idp, idend);
            pivotp = strfromp(pivotp, pivotend);
        }

        if(options->fold) {
            idp    = lowerstr(idp);
            pivotp = lowerstr(pivotp);
        }

        comparison = (*options->cmp)(idp, pivotp);

        if(comparison < 0 && !options->reverse)
            swap(a, id, pivot_id++);
        if(comparison > 0 && options->reverse)
            swap(a, id, pivot_id++);
    }

    // Might swap equal strings, worth noting because
    // it might seem wierd on the output side when fold flag is set
    // Check quicksort comments for more details.
    swap(a, pivot, pivot_id);
    return pivot_id;
}

/* If fold flag is set, the order of the passed strings (pointers) inside the
 * array might change even if the strings when folded are equal, for example:
 *
 * ```
 * char *arr[] = { "first", "First" };
 * quicksort(arr, 0, len-1, strcmp, 0, 1);
 * if (strcmp(arr[0], "First") == 0)
 *     if (strcmp(arr[1], "first") == 0)
 *         printf("Order changed");
 * ```
 *
 * This would output "Order changed", meaning it would swap the order of "first"
 * and "First" even though they are the same when fold flag is passed, the
 * reason is behind quicksort implementation (partition fn), rest assured that
 * sorting will still work fine just the ordering of passed in equivalent
 * strings might not be the same as in the input.
 * */
void quicksort(void* a[], int start, int end, flags* options) {
    int pivot;

    if(start < end) {
        pivot = partition(a, start, end, options);
        quicksort(a, start, pivot - 1, options);
        quicksort(a, pivot + 1, end, options);
    }
    return;
}
