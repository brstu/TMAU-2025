#pragma once

#include <vector>

struct ModelParams {
    int N;
    double a;
    double b;
    double c;
    double d;
};

std::vector<double> linear_model(const ModelParams& params, const std::vector<double>& u, double y0);

std::vector<double> nonlinear_model(const ModelParams& params, const std::vector<double>& u, double y0, double y1);
