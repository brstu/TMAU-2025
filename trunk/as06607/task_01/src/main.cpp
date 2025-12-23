#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

int main() {
    const int N = 30;
    const double a = 0.9;
    const double b = 0.02;
    const double c = 0.03;
    const double d = 0.1;

    // u(t)
    std::vector<double> u(N + 1);
    for (int t = 0; t <= N; t++) {
        u[t] = 1.0;
    }

    // lin
    std::vector<double> y_linear(N + 1);
    y_linear[0] = 0.0;

    for (int t = 0; t < N; t++) {
        y_linear[t + 1] = a * y_linear[t] + b * u[t];
    }

    // nonlin
    std::vector<double> y_nonlinear(N + 1);
    y_nonlinear[0] = 0.0;
    y_nonlinear[1] = 0.0;

    for (int t = 1; t < N; t++) {
        y_nonlinear[t + 1] = a * y_nonlinear[t] - b * pow(y_nonlinear[t - 1], 2) + c * u[t] + d * sin(u[t - 1]);
    }


    std::cout << std::fixed;
    std::cout << "t\tLinear y\tNonlinear y\n";
    std::cout << "------------------------------------\n";

    for (int t = 0; t <= N; t++) {
        std::cout << t << "\t" << y_linear[t] << "\t" << y_nonlinear[t] << "\n";
    }

    return 0;
}
