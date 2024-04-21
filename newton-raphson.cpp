#include "newton-raphson.h"

fix Division_Approximation(fix D) {
    fix x = 1;
    while (x <= D) {
        x <<= 1;
    }

    // Reciprocal of the next power of two as initial guess
    fix initial_guess = fix(1) / x;
    x = initial_guess;

    x = x * (fix(2) - D * x);
    x = x * (fix(2) - D * x);
    x = x * (fix(2) - D * x);
   return x;
}
