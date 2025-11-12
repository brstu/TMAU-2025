#pragma once

#include <vector>

struct Params {
    const int steps = 10;
    const double alpha = 1.2;
    const double beta  = 0.01;
    const double gamma = 0.75;
    const double delta = 0.03;
    const double init_y = 25.0;
};

std::vector<double> lin_model(const Params& prm, const std::vector<double>& u);
std::vector<double> nonlin_model(const Params& prm, const std::vector<double>& u);
