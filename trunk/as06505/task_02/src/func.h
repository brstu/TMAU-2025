#pragma once
#include <cmath>

constexpr int N = 10;

constexpr double a = 0.9;
constexpr double b = 0.001;
constexpr double c = 0.4;
constexpr double d = 0.1;

constexpr double ini_val = 10.0;

double linear(double yt, double ut);
double nonlinear(double yt, double yt_1, double ut, double ut_1);
