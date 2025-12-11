#include "t_model.h"

double model_linear(double y, double u, const ParamsLin& p) {
    return p.a * y + p.b * u;
}

double model_nonlinear(double y, double y_prev, double u, double u_prev, const ParamsNonlin& p) {
    return p.a * y
         - p.b * y_prev * y_prev
         + p.c * u
         + p.d * std::sin(u_prev);
}
