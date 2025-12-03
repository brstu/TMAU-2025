#pragma once
#include <cmath>

constexpr int N = 8;

constexpr double A = 0.85;
constexpr double B = 0.05;
constexpr double C = 0.35;
constexpr double D = 0.12;

constexpr double Y_START = 10.0;

double linearModel(double y, double u);
double nonlinearModel(double yt, double yt_prev, double ut, double ut_prev);
