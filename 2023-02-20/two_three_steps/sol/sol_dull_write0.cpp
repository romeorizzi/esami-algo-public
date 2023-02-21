/**
 *  Generic dull solution that only writes 0
 *  Romeo Rizzi, 2018-09-21
 */

#include <cstdio>

int main() {
#ifdef EVAL
    assert( freopen("output.txt", "w", stdout) );
#endif
    printf("0\n");
    return 0;
}

