#include<stdio.h>
#include<limits.h>
#include<float.h>


int main()
{
    printf("(signed - 8 bit) char min = %d, max = %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("(unsigned - 8 bit) char min = %u, max = %u\n", 0, UCHAR_MAX);
    printf("(signed - 8 bit) int min = %d, max = %d\n", _I8_MIN, _I8_MAX);
    printf("(unsigned - 8 bit) int min = %u, max = %u\n", 0, _UI8_MAX);
    printf("(signed short - 16 bit) int min = %d, max = %d\n", SHRT_MIN, SHRT_MAX);
    printf("(unsigned short - 16 bit) int min = %u, max = %u\n", 0, USHRT_MAX);
    printf("(signed - 32 bit) int min = %d, max = %d\n", INT_MIN, INT_MAX);
    printf("(unsigned - 32 bit) int min = %u, max = %u\n", 0, UINT_MAX);
    printf("(long - 32bit) int min = %ld, max = %ld\n", LONG_MIN, LONG_MAX);
    printf("(long long - 64bit) int min = %lld, max = %lld\n", LLONG_MIN, LLONG_MAX);
    printf("(long long unsigned - 64bit) int min = %llu, max = %llu\n", 0, ULLONG_MAX);
    printf("float min = %e, max = %e\n", FLT_MIN, FLT_MAX);
    printf("double min = %e, max = %e\n", DBL_MIN, DBL_MAX);
    
    return 0;
}