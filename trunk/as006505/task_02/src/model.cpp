#include "model.h"
#include <iostream>
#include <cmath>
#include <vector>

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

double nextNonlinear(const NonlinearParams& params, double u_prev, double y, double y_prev) {
    return params.a * y - params.b * (y_prev * y_prev) + params.c * u_prev + params.d * std::sin(u_prev);
}

// Новые функции, которые возвращают вектор результатов
std::vector<double> simulateLinearVec(double a, double b, double u, int steps) {
    std::vector<double> y;
    double y_curr = 0.0;

    for (int i = 0; i < steps; ++i) {
        y.push_back(y_curr);
        y_curr = nextLinear(a, b, u, y_curr);
    }
    return y;
}

std::vector<double> simulateNonlinearVec(double a, double b, double c, double d, double u, int steps) {
    std::vector<double> y;
    double y_curr = 0.0;
    double y_prev = 0.0;
    double u_prev = 0.0;

    NonlinearParams params{a, b, c, d};

    for (int i = 0; i < steps; ++i) {
        y.push_back(y_curr);
        double y_next = nextNonlinear(params, u_prev, y_curr, y_prev);
        y_prev = y_curr;
        y_curr = y_next;
        u_prev = u;
    }
    return y;
}
