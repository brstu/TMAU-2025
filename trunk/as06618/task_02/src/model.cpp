#include "model.h"
#include <cmath>

double linear_step(double y, double u, const Params& p) {
    return p.a * y + p.b * u;
}

double nonlinear_step(double y, double y_prev, double u, double u_prev, const Params& p) {
    return p.a * y
         - p.b * y_prev * y_prev
         + p.c * u
         + p.d * std::sin(u_prev);
}

std::vector<double> simulate_linear(
    double y0,
    const std::vector<double>& u,
    const Params& p)
{
    std::vector<double> y(u.size());
    y[0] = y0;

    for (size_t t = 0; t + 1 < u.size(); ++t) {
        y[t + 1] = linear_step(y[t], u[t], p);
    }
    return y;
}

std::vector<double> simulate_nonlinear(
    double y0,
    const std::vector<double>& u,
    const Params& p)
{
    std::vector<double> y(u.size());
    y[0] = y0;

    if (u.size() > 1) {
        y[1] = nonlinear_step(y[0], y[0], u[0], u[0], p);
    }

    for (size_t t = 1; t + 1 < u.size(); ++t) {
        y[t + 1] = nonlinear_step(y[t], y[t - 1], u[t], u[t - 1], p);
    }
    return y;
}
