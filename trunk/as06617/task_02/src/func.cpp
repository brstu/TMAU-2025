#include "func.h"
#include <cmath>

// Линейная модель
double linear(double y, double u) {
    return model_params::A * y + model_params::B * u;
}

// Нелинейная модель
double nonlinear(double y,
                 double y_prev,
                 double u,
                 double u_prev) {
    return model_params::A * y
         - model_params::B * (y_prev * y_prev)
         + model_params::C * u
         + model_params::D * std::sin(u_prev);
}
