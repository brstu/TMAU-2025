#include "model.h"
#include <cmath>

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev,
                       double a, double b, double c, double d) {
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
}
