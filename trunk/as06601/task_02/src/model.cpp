#include "model.h"
#include <cmath>

double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

double nonlinearModel(double a, double b_nl, double c, double d,
                      double y_t, double u_t, double u_prev) {
    return a * y_t - b_nl * y_t * y_t + c * u_t + d * sin(u_prev);
}