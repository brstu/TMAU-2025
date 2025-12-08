#include "model.h"
#include <cmath>

double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

double nonlinearModel(const NonlinearParams& p, double y_t, double u_t, double u_prev) {
    return p.a * y_t - p.b_nl * y_t * y_t + p.c * u_t + p.d * sin(u_prev);
}