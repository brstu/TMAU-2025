#pragma once
#include <vector>

struct ModelParams {
    double INPUT_OFFSET = 10.0;
    double INPUT_AMPLITUDE = 2.0;
    double INPUT_FREQUENCY = 0.5;
    double INPUT_E = 0.95;
    double a = 0.85;
    double b = 0.002;
    double c = 0.6;
    double d = 0.025;
    int time_steps = 10;
    double initial_temp = 24.0;
};

// Вычисления для моделей
double linearStep(double y, double u, const ModelParams& params);
double nonlinearStep(double y, double y_prev, double u, double u_prev, const ModelParams& params);

// Основная симуляция
std::vector<double> simulateLinear(const ModelParams& params, const std::vector<double>& u);
std::vector<double> simulateNonlinear(const ModelParams& params, const std::vector<double>& u);
