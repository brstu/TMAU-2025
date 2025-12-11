#include "temp_model.h"

double linear_model(double y_prev, double u_prev, const LinParams& p) {
    return p.a * y_prev + p.b * u_prev;
}

double nonlinear_model(double y_prev, double y_prev2, double u_prev, double u_prev2, const NonlinParams& p) {
    return p.a * y_prev - p.b * y_prev2 * y_prev2 + p.c * u_prev + p.d * std::sin(u_prev2);
}
