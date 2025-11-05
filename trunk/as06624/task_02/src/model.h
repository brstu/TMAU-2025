#pragma once
#include <cmath>

double linear_model(double y_t, double u_t, double a, double b);
double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev,
                       double a, double b, double c, double d);