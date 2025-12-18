#include <iostream>
#include <iomanip>
#include <vector>
#include "functions.h"

using system_model::run_linear;
using system_model::run_nonlinear;

static std::vector<double> make_input(std::size_t n) {
    std::vector<double> u(n, 0.0);
    for (std::size_t i = 5; i < n; ++i)
        u[i] = 10.0;
    return u;
}

int main() {
#ifdef STANDALONE
    constexpr std::size_t N = 20;

    auto u = make_input(N);
    std::vector<double> y_lin(N, 20.0);
    std::vector<double> y_non(N, 20.0);

    run_linear(u, y_lin);
    run_nonlinear(u, y_non);

    std::cout << std::fixed << std::setprecision(4);
    std::cout << " t\t u(t)\t linear\t nonlinear\n";
    std::cout << "------------------------------------------\n";

    for (std::size_t i = 0; i < N; ++i) {
        std::cout << std::setw(2) << i << "\t"
                  << std::setw(6) << u[i] << "\t"
                  << std::setw(8) << y_lin[i] << "\t"
                  << std::setw(10) << y_non[i] << "\n";
    }
#endif
    return 0;
}
