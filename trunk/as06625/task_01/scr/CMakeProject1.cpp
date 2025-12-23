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
                      double prev_state,
                      double control,
                      double prev_control,
                      const NonlinearParams& p) {
    return p.a * state
         - p.b * prev_state * prev_state
         + p.c * control
         + p.d * std::sin(prev_control);
}

double control_policy(double temperature) {
    if (temperature < 18.0) return 1.5;
    if (temperature > 28.0) return 0.0;
    return 1.0;
}

} // namespace model

int main() {
    using namespace model;

    const LinearParams lin{0.6, 0.3};
    const NonlinearParams nonlin{0.6, 0.3, 0.15, 0.08};

    double linear_state = 20.0;
    double nonlinear_state = 20.0;

    double u = 1.0;
    double u_prev = u;

    constexpr int steps = 20;

    std::cout << "Results of the Linear and Nonlinear Models\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << std::setw(6)  << "t"
              << std::setw(14) << "Linear"
              << std::setw(14) << "Nonlinear"
              << std::setw(14) << "Control\n";

    for (int t = 0; t < steps; ++t) {

        std::cout << std::setw(6)  << t
                  << std::setw(14) << std::fixed << std::setprecision(2) << linear_state
                  << std::setw(14) << nonlinear_state
                  << std::setw(14) << u << '\n';

        double next_linear =
            linear_step(linear_state, u, lin);

        double next_nonlinear =
            nonlinear_step(nonlinear_state,
                           nonlinear_state,
                           u,
                           u_prev,
                           nonlin);

        u_prev = u;
        u = control_policy(next_linear);

        linear_state = next_linear;
        nonlinear_state = next_nonlinear;
    }

    return 0;
}
