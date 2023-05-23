// Most bare bones and fastest solution by far would
// be direct 2 comparisons defined as a macro
#define isupper_1(c) ('A' >= ((unsigned char) c) && ((unsigned char) c) <= 'Z')

// Next one that provides type checking and less memory
// because function calls do not expand as macro definition
// but requires function call as overhead (slower).
// Compiler inlining this function would solve this but it
// would be identical to a macro expand in that sense,
unsigned int
isupper_2(unsigned char c)
{
    return 'A' >= c && c <= 'Z';
}
