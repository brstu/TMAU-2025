#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct LinearCfg {
    double a, b;
};

struct NonlinearCfg {
    double a, b, c, d;
};

double calc_linear(double prev_y, double prev_u, const LinearCfg& cfg) {
    return cfg.a * prev_y + cfg.b * prev_u;
}

double calc_nonlinear(double y1, double y2, double u1, double u2, const NonlinearCfg& cfg) {
    return cfg.a * y1 - cfg.b * y2 * y2 + cfg.c * u1 + cfg.d * std::sin(u2);
}

void simulate_model(int total_steps) {

    LinearCfg lin {0.75, 0.18};
    NonlinearCfg nonlin {0.75, 0.18, 0.07, 0.12};

    std::vector<double> u(total_steps, 1.0);
    std::vector<double> y_lin(total_steps, 0.0);
    std::vector<double> y_non(total_steps, 0.0);

    for (int i = 1; i < total_steps; ++i) {

        y_lin[i] = calc_linear(y_lin[i - 1], u[i - 1], lin);

        if (i == 1) {
            y_non[i] = calc_linear(y_non[i - 1], u[i - 1], {nonlin.a, nonlin.c});
        } else {
            y_non[i] = calc_nonlinear(y_non[i - 1], y_non[i - 2], u[i - 1], u[i - 2], nonlin);
        }
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Step | Linear   | Nonlinear\n";
    std::cout << "---------------------------\n";

    for (int i = 0; i < total_steps; ++i) {
        std::cout << std::setw(3) << i << " | "
                  << std::setw(8) << y_lin[i] << " | "
                  << std::setw(10) << y_non[i] << "\n";
    }
}

int main() {
    simulate_model(30);
    return 0;
}
