#pragma once
#include <cmath>

struct LinearParams {
    double a;
    double b;
};

struct NonlinearParams {
    double a;
    double bnl;
    double c;
    double d;
};

double linear_step(double y_prev, double u_prev, const LinearParams& p);
double nonlinear_step(double y_prev, double y_prev2, double u_prev, double u_prev2, const NonlinearParams& p);
