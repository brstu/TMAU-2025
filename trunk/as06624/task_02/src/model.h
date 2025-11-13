#pragma once
#include <cmath>

// Состояние системы
struct State {
    double y;        // Current output
    double y_prev;   // Previous output
    double u;        // Current control input
    double u_prev;   // Previous control input
};

// Параметры модели
struct NonlinearParams {
    double a; // Linear coefficient for current output (y)
    double b; // Nonlinear coefficient for input (u)
    double c; // Nonlinear interaction term
    double d; // Constant offset or bias
};

// Линейная модель
double linear_model(double y_t, double u_t, double a, double b);

// Нелинейная модель
double nonlinear_model(const State& s, const NonlinearParams& p);