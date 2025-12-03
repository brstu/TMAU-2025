#include "func.h"

double linear(double y, double u) {
    return a * y + b * u;
}

double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * pow(yt1, 2) + c * ut + d * sin(ut1);
}
