#pragma once
#include <cmath>

constexpr double A = 0.9;
constexpr double B_LIN = 0.2;
constexpr double B_NONLIN = 0.01;
constexpr double C = 0.15;
constexpr double D = 0.05;
constexpr double INITIAL_PREV_U = 0.0;

double linear_step(double y, double u);
double nonlinear_step(double y, double u, double prev_u);
