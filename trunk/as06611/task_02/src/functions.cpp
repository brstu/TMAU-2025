#include "functions.h"
#include <cmath>

const std::array<double, N> U = {4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 5, 6};

double linearModel(double y, double u) {
    return A * y + B * u;
}

double nonlinearModel(double y_curr, double y_prev, double u_curr, double u_prev) {
    return A * y_curr - B * pow(y_prev, 2) + C_val * u_curr + D_val * sin(u_prev);
}
