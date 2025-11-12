#include "model.h"
#include <cmath>
#include <stdexcept>

std::vector<double> lin_model(const Params& prm, const std::vector<double>& u) {
    if (static_cast<int>(u.size()) < prm.steps) {
        throw std::invalid_argument("Input vector too small");
    }
    std::vector<double> y(static_cast<size_t>(prm.steps) + 1, 0.0);
    y[0] = prm.init_y;

    for (int k = 0; k < prm.steps; ++k) {
        y[k + 1] = prm.alpha * y[k] + prm.beta * u[k];
    }
    return y;
}

std::vector<double> nonlin_model(const Params& prm, const std::vector<double>& u) {
    if (static_cast<int>(u.size()) < prm.steps) {
        throw std::invalid_argument("Input vector too small");
    }

    std::vector<double> y(static_cast<size_t>(prm.steps) + 1, 0.0);
    y[0] = prm.init_y;
    if (prm.steps >= 1) y[1] = y[0];

    for (int k = 1; k < prm.steps; ++k) {
        y[k + 1] = prm.alpha * y[k]
                   - prm.beta * std::pow(y[k - 1], 2)
                   + prm.gamma * u[k]
                   + prm.delta * std::sin(u[k - 1]);
    }
    return y;
}
