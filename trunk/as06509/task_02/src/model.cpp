#include "model.h"
#include <cmath>
#include <stdexcept>

std::vector<double> linear(const Constants& con, const std::vector<double>& u) {
    if (static_cast<int>(u.size()) < con.n) {
        throw std::invalid_argument("Vector u is too small");
    }

    std::vector<double> y(con.n + 1, 0.0);
    y[0] = con.y0;

    for (int t = 0; t < con.n; ++t) {
        y[t + 1] = con.a * y[t] + con.b * u[t];
    }

    return y;
}

std::vector<double> nonlinear(const Constants& con, const std::vector<double>& u) {
    if (static_cast<int>(u.size()) < con.n) {
        throw std::invalid_argument("Vector u is too small");
    }

    std::vector<double> y(con.n + 1, 0.0);
    y[0] = con.y0;
    y[1] = y[0];

    for (int t = 1; t < con.n; ++t) {
        y[t + 1] = con.a * y[t] - con.b * pow(y[t - 1], 2)
            + con.c * u[t] + con.d * sin(u[t - 1]);
    }

    return y;
}
