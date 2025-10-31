#pragma once
#include <cmath>

// Параметры модели (объявления)
extern const int STEPS;
extern const double a;
extern const double b;
extern const double c;
extern const double d;
extern const double Y0;

// Прототипы функций модели
double linear(double y, double u);
double nonlinear(double y, double y_prev, double u, double u_prev);
