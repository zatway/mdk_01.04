#include "Library.h"
#include <climits>

unsigned long long factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;

    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        if (result > ULLONG_MAX / i) return 0;
        result *= i;
    }
    return result;
}