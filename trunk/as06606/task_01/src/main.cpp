#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct ModelConfig {
    static constexpr double a = 0.9;
    static constexpr double b_lin = 0.2;
    static constexpr double b_nonlin = 0.01;
    static constexpr double c = 0.15;
    static constexpr double d = 0.05;

    // Special constants
    static constexpr double INITIAL_PREV_U = 0.0; // no previous input at t=0
};

struct LinearModel {
    double a;
    double b;
    LinearModel(double a_, double b_) : a(a_), b(b_) {}
    double step(double y, double u) const {
        return a * y + b * u;
    }
};

struct NonlinearModel {
    double a;
    double b_nonlin;
    double c;
    double d;
    NonlinearModel(double a_, double b_nonlin_, double c_, double d_)
        : a(a_), b_nonlin(b_nonlin_), c(c_), d(d_) {}
    double step(double y, double u, double prev_u) const {
        return a * y - b_nonlin * y * y + c * u + d * std::sin(prev_u);
    }
};

int main() {
    int n;
    double y0;
    double u_val;

    std::cout << "Enter number of steps n: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Number of steps must be positive.\n";
        return 1;
    }

    std::cout << "Enter initial temperature y0: ";
    std::cin >> y0;

    std::cout << "Enter constant heating u: ";
    std::cin >> u_val;

    LinearModel linear{ModelConfig::a, ModelConfig::b_lin};
    NonlinearModel nonlinear{ModelConfig::a, ModelConfig::b_nonlin, ModelConfig::c, ModelConfig::d};

    std::vector<double> y_lin(n + 1, 0.0);
    std::vector<double> y_nonlin(n + 1, 0.0);
    std::vector<double> u(n + 1, u_val); // constant input, but expandable for varying input

    y_lin[0] = y0;
    y_nonlin[0] = y0;

    for (int t = 0; t < n; ++t) {
        y_lin[t + 1] = linear.step(y_lin[t], u[t]);
        // At t == 0, no previous input exists → INITIAL_PREV_U
        double prev_u = (t > 0) ? u[t - 1] : ModelConfig::INITIAL_PREV_U;
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
