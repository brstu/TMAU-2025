#include "func.h"
#include <cmath>

double linear_step(double y, double u) {
    return A * y + B_LIN * u;
}

double nonlinear_step(double y, double u, double prev_u) {
    return A * y - B_NONLIN * y * y + C * u + D * std::sin(prev_u);
}
