#include <iostream>
#include <vector>
#include <cmath>
#include "func.h"

int main() {
    ModelParams params;
    std::vector<double> u(params.time_steps);

    // generate an input signal
    for (int t = 0; t < params.time_steps; ++t) {
        u[t] = params.INPUT_OFFSET + params.INPUT_AMPLITUDE * std::sin(t * params.INPUT_FREQUENCY);
    }

    auto y_lin = simulateLinear(params, u);
    auto y_nonlin = simulateNonlinear(params, u);

    std::cout << "=== Linear Model ===\n";
    std::cout << "Time\tY(t)\n";
    for (int t = 0; t <= params.time_steps; ++t) {
        std::cout << t << "\t" << y_lin[t] << "\n";
    }

    std::cout << "\n=== Nonlinear Model ===\n";
    std::cout << "Time\tY(t)\n";
    for (int t = 0; t <= params.time_steps; ++t) {
        std::cout << t << "\t" << y_nonlin[t] << "\n";
    }

    return 0;
}

