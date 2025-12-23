#include <cmath>
#include "function.h"

const int n = 10;
const double a_lin = 0.8;
const double b_lin = 0.2;
const double a_nonlin = 0.7;
const double b_nonlin = 0.1;
const double c_nonlin = 0.3;
const double d_nonlin = 0.05;
const double Y0 = 20.0;

double linear(double yt, double ut) {
    return a_lin * yt + b_lin * ut;
}

double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a_nonlin * yt - b_nonlin * pow(yt_1, 2) + c_nonlin * ut + d_nonlin * sin(ut_1);
}