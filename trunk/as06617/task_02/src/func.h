#pragma once

#include <cmath>

namespace model_params {
    // Параметры модели
    constexpr int    STEPS_COUNT = 10;
    constexpr double A = 0.99;
    constexpr double B = 0.01;
    constexpr double C = 0.5;
    constexpr double D = 0.1;
    constexpr double INITIAL_Y = 18.0;
}

// Функции динамики системы
double linear(double y, double u);

double nonlinear(double current_y,
                 double previous_y,
                 double control_u,
                 double previous_u);

