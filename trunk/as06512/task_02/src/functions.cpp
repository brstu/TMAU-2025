#pragma once
#include "functions.h"
#include <cmath>
///Linear mathematical model y??? = a * y? + b * u
double linear(double y, double u_val) {
    return a * y + b * u_val;
}

///Nonlinear mathematical model y??? = a * y? - b * y???? + c * u? + d * sin(u???)
double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * yt1 * yt1 + c * ut + d * sin(ut1);
}
