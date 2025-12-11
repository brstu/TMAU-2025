#pragma once
#include <cmath>

struct LinParams {
    double a;
    double b;
};

struct NonlinParams {
    double a;
    double b;
    double c;
    double d;
};

double linear_model(double y_prev, double u_prev, const LinParams& p);

double nonlinear_model(double y_prev, double y_prev2, double u_prev, double u_prev2, const NonlinParams& p);
