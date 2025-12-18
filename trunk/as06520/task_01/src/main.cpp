#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct LinearParams {
    double alpha;
    double beta;
};

struct NonlinearParams {
    double alpha;
    double beta;
    double gamma;
    double delta;
};

double simulate_linear(double temp, double heat, const LinearParams& p) {
    return p.alpha * temp + p.beta * heat;
}

double simulate_nonlinear(double temp_now, double temp_prev, double heat_now, double heat_prev, const NonlinearParams& p) {
    return p.alpha * temp_now - p.beta * temp_prev * temp_prev + p.gamma * heat_now + p.delta * std::sin(heat_prev);
}

void run_simulation(int steps, const LinearParams& lin, const NonlinearParams& nonlin) {
    std::vector<double> heat_input(steps, 1.0);
    std::vector<double> temp_lin(steps, 0.0);
    std::vector<double> temp_nonlin(steps, 0.0);

    for (int i = 1; i < steps; ++i) {
        temp_lin[i] = simulate_linear(temp_lin[i - 1], heat_input[i - 1], lin);

        if (i > 1) {
            temp_nonlin[i] = simulate_nonlinear(temp_nonlin[i - 1], temp_nonlin[i - 2],
                                                heat_input[i - 1], heat_input[i - 2], nonlin);
        } else {
            temp_nonlin[i] = simulate_linear(temp_nonlin[i - 1], heat_input[i - 1], {nonlin.alpha, lin.beta});
        }
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Time\tLinearTemp\tNonlinearTemp\n";
    for (int i = 0; i < steps; ++i) {
        std::cout << i << "\t" << temp_lin[i] << "\t\t" << temp_nonlin[i] << "\n";
    }
}

int main() {
    int total_steps = 30;

    LinearParams lin_params{0.8, 0.15};
    NonlinearParams nonlin_params{0.8, 0.15, 0.05, 0.1};

    run_simulation(total_steps, lin_params, nonlin_params);

    return 0;
}
