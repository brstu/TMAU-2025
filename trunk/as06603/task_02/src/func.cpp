#include "func.h"
#include <cmath>

// Параметры модели (слегка изменены для уникальности)
const int    STEPS = 12;
const double a = 0.95;
const double b = 0.05;
const double c = 0.45;
const double d = 0.15;
const double Y0 = 20.0;

namespace Model {

double linearModel(double y, double u) {
    return a * y + b * u;
}

double nonlinearModel(double y, double y_prev, double u, double u_prev) {
    return a * y - b * std::pow(y_prev, 2) + c * u + d * std::sin(u_prev);
}

} // namespace Model
