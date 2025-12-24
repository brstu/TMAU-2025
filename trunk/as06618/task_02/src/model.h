#pragma once
#include <vector>

struct Params {
    double a;
    double b;
    double c;
    double d;
};

double linear_step(double y, double u, const Params& p);
double nonlinear_step(double y, double y_prev, double u, double u_prev, const Params& p);

std::vector<double> simulate_linear(
    double y0,
    const std::vector<double>& u,
    const Params& p
);

std::vector<double> simulate_nonlinear(
    double y0,
    const std::vector<double>& u,
    const Params& p
);
