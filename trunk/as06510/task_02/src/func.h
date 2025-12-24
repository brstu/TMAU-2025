#pragma once
#include <cmath>

constexpr int steps = 10;

constexpr double kA = 0.95;
constexpr double kB = 0.02;
constexpr double kC = 0.45;
constexpr double kD = 0.15;

constexpr double yStart = 18;

double linearModel(double y, double u);
double nonlinearModel(double y, double yPrev, double u, double uPrev);
