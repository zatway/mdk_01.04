#include "MathLib.h"
#include <cmath>

namespace MathLibrary {
    double Arithmetic::Add(double a, double b) {
        return a + b;
    }

    double Arithmetic::Subtract(double a, double b) {
        return a - b;
    }

    double Arithmetic::Multiply(double a, double b) {
        return a * b;
    }

    double Arithmetic::Divide(double a, double b) {
        if (b == 0) return 0;
        return a / b;
    }

    double Arithmetic::Pow(double a, double b) {
        return std::pow(a, b);
    }

    double Arithmetic::Root(double a, double b) {
        if (b == 0) return 0;
        return std::pow(a, 1.0 / b);
    }
}