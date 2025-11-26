#pragma once
#include <vector>

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

double nextLinear(double a, double b, double u, double y);
double nextNonlinear(const NonlinearParams& params, double u_prev, double y, double y_prev);

std::vector<double> simulateLinearVec(double a, double b, double u, int steps);
std::vector<double> simulateNonlinearVec(double a, double b, double c, double d, double u, int steps);