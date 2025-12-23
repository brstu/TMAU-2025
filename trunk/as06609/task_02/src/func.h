#pragma once
#include <cmath>

constexpr int N = 10;
constexpr double A = 0.99;
constexpr double B = 0.01;
constexpr double C = 0.5;
constexpr double D = 0.1;
constexpr double Y_START = 18.0;

double linearModel(double y, double u);
double nonlinearModel(double y, double y_prev, double u, double u_prev);
