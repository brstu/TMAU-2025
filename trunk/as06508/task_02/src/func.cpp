#include "func.h"
#include <cmath>

// Один шаг линейной модели
double linearStep(double y, double u, const ModelParams& params) {
    return params.a * y + params.b * u;
}

// Один шаг нелинейной модели
double nonlinearStep(double y, double y_prev, double u, double u_prev, const ModelParams& params) {
    return params.a * y - params.b * std::pow(y_prev, 2) + params.c * u + params.d * std::sin(u_prev);
}

// Симуляция линейной модели
std::vector<double> simulateLinear(const ModelParams& params, const std::vector<double>& u) {
    std::vector<double> y(params.time_steps + 1);
    y[0] = params.initial_temp;
    for (int t = 0; t < params.time_steps; ++t) {
        y[t + 1] = linearStep(y[t], u[t], params);
    }
    return y;
}

// Симуляция нелинейной модели
std::vector<double> simulateNonlinear(const ModelParams& params, const std::vector<double>& u) {
    std::vector<double> y(params.time_steps + 1);
    y[0] = params.initial_temp;
    y[1] = y[0] * params.INPUT_E;

    for (int t = 1; t < params.time_steps; ++t) {
        y[t + 1] = nonlinearStep(y[t], y[t - 1], u[t], u[t - 1], params);
    }
    return y;
}
