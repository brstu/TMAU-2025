#pragma once
#include <cmath>

constexpr int TIME_STEPS = 10;

constexpr double PARAM_A = 0.99;
constexpr double PARAM_B = 0.01;
constexpr double PARAM_C = 0.5;
constexpr double PARAM_D = 0.1;

constexpr double INITIAL_Y = 18;

double linearModel(double currentY, double inputU);
double nonlinearModel(double yt, double yt_1, double ut, double ut_1);
