#pragma once

#ifdef _WIN32
    #ifdef FACTORIALLIB_EXPORTS
        #define FACTORIAL_API __declspec(dllexport)
    #else
        #define FACTORIAL_API __declspec(dllimport)
    #endif
#else
    #define FACTORIAL_API
#endif

extern "C" {
    FACTORIAL_API unsigned long long factorial(int n);
}