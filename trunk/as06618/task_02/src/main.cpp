#include <iostream>
#include <vector>
#include <iomanip>
#include "model.h"

int main() {
    const Params p{0.92, 0.08, 0.07, 0.04};
    const size_t N = 20;
    const double y0 = 20.0;

    std::vector<double> u(N, 0.0);
    for (size_t i = 5; i < N; ++i) {
        u[i] = 10.0;
    }

    auto y_lin = simulate_linear(y0, u, p);
    auto y_non = simulate_nonlinear(y0, u, p);

    std::cout << std::fixed << std::setprecision(3);
    std::cout << "t\tu\tlinear\t\tnonlinear\n";
    std::cout << "-----------------------------------\n";

    for (size_t i = 0; i < N; ++i) {
        std::cout << i << '\t'
                  << u[i] << '\t'
                  << y_lin[i] << "\t\t"
                  << y_non[i] << '\n';
    }
}
