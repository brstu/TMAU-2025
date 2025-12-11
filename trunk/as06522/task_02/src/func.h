#pragma once
#include <cmath>

constexpr int TIME_STEPS = 10;

constexpr double COEFFICIENT_A = 0.99;
constexpr double COEFFICIENT_B = 0.01;
constexpr double COEFFICIENT_C = 0.5;
constexpr double COEFFICIENT_D = 0.1;

constexpr double INITIAL_VALUE = 18;

double linearModel(double currentValue, double controlInput);
double nonlinearModel(double currentValue, double previousValue, double controlInput, double previousControlInput);
