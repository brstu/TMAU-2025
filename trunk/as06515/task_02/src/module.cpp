#include "module.h"
#include <cmath>

void compute_linear(int N, double a, double b, const std::vector<double>& u, std::vector<double>& y_lin) {
    for (int t = 0; t < N; ++t) {
        y_lin[t + 1] = a * y_lin[t] + b * u[t];
    }
}

void compute_nonlinear(int N, double a, double b, double c, double d, const std::vector<double>& u, std::vector<double>& y_nl) {
    for (int t = 1; t < N; ++t) {
        y_nl[t + 1] = a * y_nl[t]
                    - b * y_nl[t - 1] * y_nl[t - 1]
                    + c * u[t]
                    + d * std::sin(u[t - 1]);
    }
}