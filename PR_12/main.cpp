#include <iostream>
#include <windows.h>
#include "Library.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    for (int n = -1; n <= 20; ++n) {
        unsigned long res = factorial(n);
        if (n < 0) {
            std::cout << n << "! - отрицательное\n";
        } else if (res == 0 && n > 1) {
            std::cout << n << "! - переполнение\n";
        } else {
            std::cout << n << "! = " << res << '\n';
        }
    }

    return 0;
}