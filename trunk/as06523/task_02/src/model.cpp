#include "model.h"
#include <cmath>

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, const Coeffs& coeffs) {
    return coeffs.a * y_t - coeffs.b * y_prev * y_prev + coeffs.c * u_t + coeffs.d * sin(u_prev);
}
