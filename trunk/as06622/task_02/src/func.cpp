#include "func.h"
#include <cmath>

// Определения параметров модели
const int    STEPS = 10;
const double a = 0.99;
const double b = 0.01;
const double c = 0.5;
const double d = 0.1;
const double Y0 = 18.0;

// Линейная динамика
double linear(double y, double u) {
    return a * y + b * u;
}

// Нелинейная динамика
double nonlinear(double y, double y_prev, double u, double u_prev) {
    return a * y - b * std::pow(y_prev, 2) + c * u + d * std::sin(u_prev);
}
