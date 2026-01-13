#include <iostream>
#include "MathLib.h"
#include <Windows.h>

using namespace std;
using namespace MathLibrary;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    double a = 9, b = 3;

    cout << a << " + " << b << " = " << Arithmetic::Add(a, b) << endl;
    cout << a << " - " << b << " = " << Arithmetic::Subtract(a, b) << endl;
    cout << a << " * " << b << " = " << Arithmetic::Multiply(a, b) << endl;
    cout << a << " / " << b << " = " << Arithmetic::Divide(a, b) << endl;

    cout << a << " ^ " << b << " = " <<Arithmetic::Pow(a, b) << endl;
    cout << a << " √ " << b << " = " << Arithmetic::Root(a, b) << endl;

    return 0;
}