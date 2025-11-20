#include <iostream>
#include <vector>
#include <cmath>
#include "model.h"



int main() {
    NonlinearParams params{0.8, 0.2, 0.1, 0.05};
    int N = 20;

    std::vector<double> y(N + 1, 0.0);
    std::vector<double> u(N + 1, 0.0);

    // формируем управление
    for (int t = 0; t <= N; t++) {
        u[t] = (t < 5) ? 0.0 : 1.0;
    }

    std::cout << "linear model" << std::endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], params.a, params.b);
        std::cout << "t=" << t + 1 << "  y=" << y[t + 1] << std::endl;
    }

    std::fill(y.begin(), y.end(), 0.0);

    std::cout << "\nnon linear model" << std::endl;
    for (int t = 0; t < N; t++) {
        double y_prev = (t == 0) ? 0.0 : y[t - 1];
        double u_prev = (t == 0) ? 0.0 : u[t - 1];
        State s{y[t], y_prev, u[t], u_prev};
        y[t + 1] = nonlinear_model(s, params);
        std::cout << "t=" << t + 1 << "  y=" << y[t + 1] << std::endl;
    }

    return 0;
}