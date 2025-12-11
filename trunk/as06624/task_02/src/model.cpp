#include "model.h"

double linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

double nonlinear_model(const State& s, const NonlinearParams& p) {
    return p.a * s.y
         - p.b * s.y_prev * s.y_prev
         + p.c * s.u
         + p.d * std::sin(s.u_prev);
}