#include "model.h"
#include <vector>
#include <cmath>

double nonlinearModel(double a, double b_nl, double c, double d,
                      double y_t, double u_t, double u_prev) {
    return a * y_t - b_nl * y_t * y_t + c * u_t + d * sin(u_prev);
}

double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

std::vector<double> simulateLinear(int n, double a, double b, double y0, double u0) {
    std::vector<double> y(n + 1);
    y[0] = y0;
    for (int t = 0; t < n; t++) {
        y[t + 1] = linearModel(a, b, y[t], u0);
    }
    return y;
}

std::vector<double> simulateNonlinear(int n, double a, double b_nl, double c, double d, double y0, double u0) {
    std::vector<double> y(n + 1);
    y[0] = y0;
    for (int t = 0; t < n; t++) {
        double u_prev = u0;
        y[t + 1] = nonlinearModel(a, b_nl, c, d, y[t], u0, u_prev);
    }
    return y;
}