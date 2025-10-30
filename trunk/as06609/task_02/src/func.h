#pragma once
#include <cmath>

const int N = 10;
const double A = 0.99;
const double B = 0.01;
const double C = 0.5;
const double D = 0.1;
const double Y_START = 18.0;

double linear(double y, double u);
double nonlinear(double y, double y_prev, double u, double u_prev);
