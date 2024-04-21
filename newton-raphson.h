#ifndef NEWTON_RAPHSON_FIXED_H
#define NEWTON_RAPHSON_FIXED_H

#include <ap_fixed.h>

// Define the fixed-point type using the precision given in the image
typedef ap_fixed<32, 16, AP_TRN, AP_WRAP> fix;

// Function prototype for the Newton-Raphson method to find the reciprocal of a fixed-point number
fix Division_Approximation(fix D);

#endif

