#pragma once

#include <vector>

struct Constants {
    const int n = 10;
    const double a = 1.2;
    const double b = 0.01;
    const double c = 0.75;
    const double d = 0.03;
    const double y0 = 25.0;
};

std::vector<double> linear(const Constants& con, const std::vector<double>& u);
std::vector<double> nonlinear(const Constants& con, const std::vector<double>& u);

