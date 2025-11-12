#pragma once

#include <vector>

struct Params {
    int steps = 10;
    double alpha = 1.2;
    double beta  = 0.01;
    double gamma = 0.75;
    double delta = 0.03;
    double init_y = 25.0;
};

std::vector<double> lin_model(const Params& prm, const std::vector<double>& u);
std::vector<double> nonlin_model(const Params& prm, const std::vector<double>& u);
