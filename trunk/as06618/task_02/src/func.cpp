#include "func.h"

// Линейная динамика
double linear(double y, double u) {
    return a * y + b * u;
}

// Нелинейная динамика
double nonlinear(double y, double y_prev, double u, double u_prev) {
    return a * y - b * std::pow(y_prev, 2) + c * u + d * std::sin(u_prev);
}
