#include "func.h"

// linear model
double linear(double yt, double ut) {
    return a * yt + b * ut;
}

// nonlinear model
double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a * yt
           - b * (yt_1 * yt_1)
           + c * ut
           + d * std::sin(ut_1);
}
