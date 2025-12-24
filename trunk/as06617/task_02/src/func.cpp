#include "func.h"
#include <cmath>

namespace model_params {
    constexpr int    STEPS_COUNT = 10;
    constexpr double A = 0.99;
    constexpr double B = 0.01;
    constexpr double C = 0.5;
    constexpr double D = 0.1;
    constexpr double INITIAL_Y = 18.0;
}

// Линейная модель
inline double linear(double y, double u) {
    return model_params::A * y + model_params::B * u;
}

// Нелинейная модель
inline double nonlinear(double y,
                         double y_prev,
                         double u,
                         double u_prev) {
    return model_params::A * y
         - model_params::B * (y_prev * y_prev)
         + model_params::C * u
         + model_params::D * std::sin(u_prev);
}
