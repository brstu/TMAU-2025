#include <iostream>
#include <vector>
#include <iomanip>
#include "t_model.h"

void run(int steps) {
    const ParamsLin PL{0.77, 0.29};
    const ParamsNonlin PN{0.86, 0.15, 0.10, 0.11};

    std::vector<double> yL(steps, 0.0);
    std::vector<double> yN(steps, 0.0);
    std::vector<double> u(steps, 1.0);

    for (int t = 1; t < steps; ++t) {

        yL[t] = model_linear(yL[t - 1], u[t - 1], PL);

        if (t == 1) {
            ParamsLin tmp{PN.a, PN.c};
            yN[t] = model_linear(yN[t - 1], u[t - 1], tmp);
        } else {
            yN[t] = model_nonlinear(yN[t - 1], yN[t - 2], u[t - 1], u[t - 2], PN);
        }
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << " t |    linear   |  nonlinear\n";
    std::cout << "---------------------------------\n";

    for (int t = 0; t < steps; ++t) {
        std::cout << std::setw(2) << t << " | " << std::setw(10) << yL[t] << " | " << std::setw(10) << yN[t] << "\n";
    }
}

int main() {

    run(30);

    return 0;
}
