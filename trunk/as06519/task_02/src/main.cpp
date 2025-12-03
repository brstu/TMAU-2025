#include <iostream>
#include <vector>
#include <iomanip>
#include "temp_model.h"

void run_model(int steps) {
    LinParams lin{0.75, 0.18};
    NonlinParams nonlin{0.75, 0.18, 0.07, 0.12};

    std::vector<double> u(steps, 1.0);
    std::vector<double> y_lin(steps, 0.0);
    std::vector<double> y_nonlin(steps, 0.0);

    for (int t = 1; t < steps; ++t) {
        y_lin[t] = linear_model(y_lin[t - 1], u[t - 1], lin);

        if (t < 2) {
            y_nonlin[t] = linear_model(y_nonlin[t - 1], u[t - 1], {nonlin.a, nonlin.c});
        } else {
            y_nonlin[t] = nonlinear_model(
                y_nonlin[t - 1], y_nonlin[t - 2],
                u[t - 1], u[t - 2], nonlin
            );
        }
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n--- Temperature Simulation ---\n";
    std::cout << "Step |  Linear   |  Nonlinear\n";
    std::cout << "-------------------------------\n";

    for (int t = 0; t < steps; ++t) {
        std::cout << std::setw(3) << t << " | " << std::setw(8)
                  << y_lin[t] << " | " << std::setw(10)
                  << y_nonlin[t] << "\n";
    }
}

int main() {
    run_model(20);
    return 0;
}
