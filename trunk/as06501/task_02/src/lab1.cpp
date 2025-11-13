#include "lab1.h"
#include <cmath>
double linear(double y, double u) {
    return a * y + b * u;
}

double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * yt1 * yt1 + c * ut + d * sin(ut1);
}
