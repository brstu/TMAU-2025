#pragma once

#include <cmath>

inline constexpr int STEPS = 10;
inline constexpr double a = 0.99;
inline constexpr double b = 0.01;
inline constexpr double c = 0.5;
inline constexpr double d = 0.1;
inline constexpr double Y0 = 18.0;

double linear(double y, double u);
double nonlinear(double y, double y_prev, double u, double u_prev);
