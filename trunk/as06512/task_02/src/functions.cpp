#pragma once
#include "functions.h"
#include <cmath>
double linear(double y, double u_val) {
    return a * y + b * u_val;
}

double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * yt1 * yt1 + c * ut + d * sin(ut1);
}
