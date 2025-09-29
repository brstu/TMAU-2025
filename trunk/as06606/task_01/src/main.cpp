#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct LinearModel {
    double a, b;
    double step(double y, double u) const {
        return a * y + b * u;
    }
};

struct NonlinearModel {
    double a, b_nl, c, d;
    double step(double y, double u, double prev_u) const {
        return a * y - b_nl * y * y + c * u + d * std::sin(prev_u);
    }
};

int main() {
    int n;
    double y0;
    double u_val;

    double a = 0.9;
    double b = 0.2;
    double b_nl = 0.01;
    double c = 0.15;
    // d: Amplitude of the nonlinear input effect (weight of the sinusoidal term modeling actuator dynamics), chosen as 0.05 for moderate nonlinearity
    double d = 0.05;

    std::cout << "Enter number of steps n: ";
    std::cin >> n;
    std::cout << "Enter initial temperature y0: ";
    std::cin >> y0;
    std::cout << "Enter constant heating u: ";
    std::cin >> u_val;

    LinearModel linear{a, b};
    NonlinearModel nonlinear{a, b_nl, c, d};

    std::vector<double> y_lin(n + 1, 0.0);
    std::vector<double> y_nonlin(n + 1, 0.0);
    std::vector<double> u(n + 1, u_val);

    y_lin[0] = y0;
    y_nonlin[0] = y0;

    for (int t = 0; t < n; ++t) {
        y_lin[t + 1] = linear.step(y_lin[t], u[t]);
        // For the first step (t == 0), there is no previous u value, so use 0.0 as the default.
        double prev_u = (t > 0) ? u[t - 1] : 0.0;
        y_nonlin[t + 1] = nonlinear.step(y_nonlin[t], u[t], prev_u);
    }

    std::cout << "\nSimulation results:\n";
    std::cout << "Step\tLinear\t\tNonlinear\n";
    std::cout << "---------------------------------\n";
    for (int t = 0; t <= n; ++t) {
        std::cout << t << "\t" 
                  << std::fixed << std::setprecision(4) << y_lin[t] << "\t\t"
                  << y_nonlin[t] << "\n";
    }

    return 0;
}
