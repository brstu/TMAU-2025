#include "model.h"

double compute_linear_model(double y_prev, double u, double a, double b) {
    return a * y_prev + b * u;
}

double compute_nonlinear_model(double y_curr, double y_prev, double u_curr, double u_prev, double a, double b, double c, double d) {
    return a * y_curr + b * u_curr + c * y_prev * u_prev + d * u_prev * u_prev;
}
