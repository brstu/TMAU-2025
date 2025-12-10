#include "model.h"
#include <cmath>

double linear_step(double y_prev, double u_prev, const LinearParams& p) {
    return p.a * y_prev + p.b * u_prev;
}

double nonlinear_step(double y_prev, double y_prev2, double u_prev, double u_prev2, const NonlinearParams& p) {
    return p.a * y_prev - p.bnl * (y_prev2 * y_prev2) + p.c * u_prev + p.d * std::sin(u_prev2);
}
