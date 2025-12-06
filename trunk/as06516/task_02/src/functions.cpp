#include "functions.h"
#include <cmath>

const double a = 0.92;
const double b_lin = 0.08;    
const double b_non = 0.005;   
const double c = 0.07;
const double d = 0.04;

double linear(double yt, double ut) {
    return a * yt + b_lin * ut;
}

double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b_non * yt1 * yt1 + c * ut + d * std::sin(ut1);  
}
