#include "func.h"

double linearModel(double y, double u) {
    return A * y + B * u;
}

double nonlinearModel(double y, double y_prev, double u, double u_prev) {
    return A * y - B * pow(y_prev, 2) + C * u + D * sin(u_prev);
}
