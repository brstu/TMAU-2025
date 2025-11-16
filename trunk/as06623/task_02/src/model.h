#pragma once
#include <vector>

constexpr double coeffA = 0.1;
constexpr double coeffB = 0.2;
constexpr double coeffC = 0.3;
constexpr double coeffD = 0.4;
constexpr double initialTemperature = 20.0;
constexpr int iterationsCount = 50;

std::vector<double> simulateLinear(double controlInput);
std::vector<double> simulateNonlinear(double controlInput);