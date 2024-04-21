#include <iostream>
#include "newton-raphson.h"

int main() {

    fix D = 2860.29;
    //fix initial_guess = 0.00781;
    //int max_iterations = 3;

    fix reciprocal = Division_Approximation(D);

    std::cout << "Reciprocal of " << D.to_float() << " using Newton-Raphson is approximately: " << reciprocal.to_float() << std::endl;

    return 0;
}

