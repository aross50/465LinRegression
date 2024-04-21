// #include "newton-raphson.h"

// fix Division_Approximation(fix D) {
//     fix x = 1;
//     while (x <= D) {
//         x <<= 1;
//     }

//     // Reciprocal of the next power of two as initial guess
//     fix initial_guess = fix(1) / x;
//     x = initial_guess;

//     x = x * (fix(2) - D * x);
//     x = x * (fix(2) - D * x);
//     x = x * (fix(2) - D * x);
//    return x;
// }
#include "newton-raphson.h"

fix Division_Approximation(fix D) {
    fix x = 1;
    int shift_count = 0;
    const int total_width = 32;
    const int int_width = 16;

    while (x <= D) {
        x <<= 1;
        shift_count++;
    }

    // Now, calculate the number of fractional bits
    int frac_width = total_width - int_width;


    fix initial_guess = 0;
    unsigned int bitmask = 1 << (frac_width - shift_count);

    initial_guess = reinterpret_cast<fix&>(bitmask);

    x = initial_guess;

    x = x * (fix(2) - D * x);
    x = x * (fix(2) - D * x);
    x = x * (fix(2) - D * x);

   return x;
}



