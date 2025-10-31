#pragma once

struct NonlinearParams {
    double y_curr;
    double y_prev;
    double u_curr;
    double u_prev;
    double a;
    double b;
    double c;
    double d;
};

double compute_linear_model(double y_prev, double u, double a, double b);
double compute_nonlinear_model(const NonlinearParams& params);
