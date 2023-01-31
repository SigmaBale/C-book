#include<stdio.h>
#define SIZE 100

int binsearch1(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main()
{
    int result, i;
    int v[SIZE];
    
    for(i = 0; i < SIZE; i++)
        v[i] = 1+i;

    result = binsearch1(15, v, SIZE);
    printf("Found result of first binary search: index %d\n", result);
    result = binsearch2(58, v, SIZE);
    printf("Found result of second binary search: index %d\n", result);
    return 0;
}

int binsearch2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while(low <= high && x != v[mid]) {
        mid = (low + high)/2;
        if(x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return (x == v[mid]) ? mid : -1;
}

int binsearch1(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;               
    while (low <= high) {
        mid = (low+high)/2;     
        if (x < v[mid])         
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else {
            return mid;
        }
    }
    return -1;
}