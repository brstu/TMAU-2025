#pragma once
#include <cmath>

constexpr int N = 8;

constexpr double a = 0.85;
constexpr double b = 0.05;
constexpr double c = 0.35;
constexpr double d = 0.12;

constexpr double start_value = 10.0;

double linear(double y, double u);
double nonlinear(double yt, double yt1, double ut, double ut1);

