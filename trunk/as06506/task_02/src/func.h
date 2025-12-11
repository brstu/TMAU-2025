#pragma once
#include <cmath>

constexpr int N = 10;

constexpr double A = 0.97;
constexpr double B = 0.015;
constexpr double C = 0.45;
constexpr double D = 0.12;

constexpr double Y_START = 20;

double linearModel(double y, double u);
double nonlinearModel(double y_curr, double y_prev, double u_curr, double u_prev);
