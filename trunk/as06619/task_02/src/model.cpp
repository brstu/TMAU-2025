#include "model.h"
#include <cmath>

double compute_linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

double compute_nonlinear_model(const NonlinearParams& p) {
    return p.a * p.y_curr - p.b * p.y_prev * p.y_prev + p.c * p.u_curr + p.d * sin(p.u_prev);
}
