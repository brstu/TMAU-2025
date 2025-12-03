#include "func.h"

double linearModel(double y, double u) {
    return A * y + B * u;
}

double nonlinearModel(double yt, double yt_prev, double ut, double ut_prev) {
    return A * yt - B * pow(yt_prev, 2) + C * ut + D * sin(ut_prev);
}
