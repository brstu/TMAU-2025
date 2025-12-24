#include "model.h"
#include <cmath>

std::vector<double> linear_model(const ModelParams& params, const std::vector<double>& u, double y0) {
    std::vector<double> y(params.N + 1);
    y[0] = y0;

    for (int t = 0; t < params.N; ++t) {
        y[t + 1] = params.a * y[t] + params.b * u[t];
    }

    return y;
}

std::vector<double> nonlinear_model(const ModelParams& params, const std::vector<double>& u, double y0, double y1) {
    std::vector<double> y(params.N + 1);
    y[0] = y0;
    y[1] = y1;

    for (int t = 1; t < params.N; ++t) {
        y[t + 1] = params.a * y[t] - params.b * std::pow(y[t - 1], 2) + params.c * u[t] + params.d * std::sin(u[t - 1]);
    }

    return y;
}
