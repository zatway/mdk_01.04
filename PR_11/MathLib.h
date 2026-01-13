#ifndef PR_11_MATHLIB_H
#define PR_11_MATHLIB_H

namespace MathLibrary {
    class Arithmetic {
    public:
        static double Add(double a, double b);
        static double Subtract(double a, double b);
        static double Multiply(double a, double b);
        static double Divide(double a, double b);

        static double Pow(double a, double b);
        static double Root(double a, double b);
    };
}

#endif