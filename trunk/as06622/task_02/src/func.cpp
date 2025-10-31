#include "func.h"
#include <cmath>

// Линейная динамика
double linModel(double y, double u) {
    return K1 * y + K2 * u;
}

// Нелинейная динамика
double nonlinEq(double y, double y_prev, double u, double u_prev) {
    return K1 * y + K3 * u - K2 * pow(y_prev, 2) + K4 * sin(u_prev);
}