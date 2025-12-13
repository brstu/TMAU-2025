#include "func.h"

double linear(double yt, double ut) {
    return a * yt + b * ut;
}

double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a * yt - b * (yt_1 * yt_1) + c * ut + d * sin(ut_1);
}
