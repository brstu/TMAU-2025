#include <iostream>
#include <iomanip>
#include <cmath>

namespace model {

struct LinearParams {
    double a;
    double b;
};

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

double linear_step(double state, double control, const LinearParams& p) {
    return p.a * state + p.b * control;
}

double nonlinear_step(double state,
                      double control,
                      double prev_control,
                      const NonlinearParams& p) {
    return p.a * state
         - p.b * state * state
         + p.c * control
         + p.d * std::sin(prev_control - 1.0);
}

double control_policy(double temperature) {
    if (temperature < 18.0) return 1.5;
    if (temperature > 28.0) return 0.0;
    return 1.0;
}

} // namespace model

int main() {
    using namespace model;

    const LinearParams lin{0.8, 0.2};
    const NonlinearParams nonlin{0.7, 0.005, 0.25, 0.1};

    double linear_state   = 20.0;
    double nonlinear_state = 20.0;

    double u = 1.0;
    double u_prev = u;

    constexpr int horizon = 30;

    std::cout << "Эволюция температурных моделей\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::setw(6)  << "t"
              << std::setw(14) << "Linear"
              << std::setw(14) << "Nonlinear"
              << std::setw(14) << "Control\n";

    for (int step = 0; step < horizon; ++step) {

        std::cout << std::setw(6)  << step
                  << std::setw(14) << std::fixed << std::setprecision(2) << linear_state
                  << std::setw(14) << nonlinear_state
                  << std::setw(14) << u << '\n';

        const double next_linear =
            linear_step(linear_state, u, lin);

        const double next_nonlinear =
            nonlinear_step(nonlinear_state, u, u_prev, nonlin);

        u_prev = u;
        u = control_policy(next_linear);

        linear_state = next_linear;
        nonlinear_state = next_nonlinear;
    }

    return 0;
}