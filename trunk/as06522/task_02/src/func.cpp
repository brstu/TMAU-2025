#include "func.h"

double linearModel(double currentValue, double controlInput) {
    return COEFFICIENT_A * currentValue + COEFFICIENT_B * controlInput;
}

double nonlinearModel(double currentValue, double previousValue, double controlInput, double previousControlInput) {
    return COEFFICIENT_A * currentValue
        - COEFFICIENT_B * pow(previousValue, 2)
        + COEFFICIENT_C * controlInput
        + COEFFICIENT_D * sin(previousControlInput);
}
