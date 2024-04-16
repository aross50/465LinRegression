#include <ap_fixed.h>

// Definition of fixed-point type with 32 bits, 16 integer bits, and rounding and overflow modes.
typedef ap_fixed<32, 16, AP_TRN, AP_WRAP> fix;

// Function to approximate the reciprocal of a number using Newton-Raphson method
fix Division_Approximation(fix D, int iterations = 3) {

	// Given the determinate of (X^T)(X) = 2856.26, we must find the reciprocal next highest power of two
	// (next highest power of two is 4096) which would be 0.000024414.
	fix x_i = fix(0.00024414);

    x_i = x_i * (fix(2) - D * x_i);
    x_i = x_i * (fix(2) - D * x_i);
    x_i = x_i * (fix(2) - D * x_i);


    return x_i;
}

