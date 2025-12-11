#pragma once
#include <vector>
constexpr double a = 0.1;
constexpr double b = 0.2;
constexpr double c = 0.3;
constexpr double d = 0.4;
constexpr double InpTemp = 20;
constexpr int iterations = 50;
std::vector <double> linear(double u);
std::vector <double> nonlinear(double u);
