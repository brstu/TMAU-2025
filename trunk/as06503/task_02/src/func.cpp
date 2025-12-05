#include "func.h"
#include <cmath>
// linear model
double linear(double yt, double ut) {
    return a * yt + b * ut;
}
// nonlinear model
double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a * yt - b * pow(yt_1, 2) + c * ut + d * sin(ut_1);
}