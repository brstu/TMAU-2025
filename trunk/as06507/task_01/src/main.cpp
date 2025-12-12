#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct LinearParams {
    double a;
    double b;
};

struct NonlinearParams {
    double a;
    double bnl;
    double c;
    double d;
};

double linear_step(double y_prev, double u_prev, const LinearParams& p) {
    return p.a * y_prev + p.b * u_prev;
}

double nonlinear_step(double y_prev, double y_prev2, double u_prev, double u_prev2, const NonlinearParams& p) {
    return p.a * y_prev - p.bnl * y_prev2 * y_prev2 + p.c * u_prev + p.d * std::sin(u_prev2);
}

void run_simulation(int steps) {
    LinearParams lp{0.86, 0.23};
    NonlinearParams np{0.69, 0.15, 0.10, 0.21};

    std::vector<double> u(steps, 1.0);
    std::vector<double> y_lin(steps);
    std::vector<double> y_non(steps);

    y_lin[0] = 0.0;
    y_non[0] = 0.0;

    for (int t = 1; t < steps; ++t) {
        y_lin[t] = linear_step(y_lin[t-1], u[t-1], lp);

        if (t == 1) {
            y_non[t] = linear_step(y_non[t-1], u[t-1], {np.a, np.c});
        } else {
            y_non[t] = nonlinear_step(y_non[t-1], y_non[t-2], u[t-1], u[t-2], np);
        }
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "  t |     lin |     nonlin\n";
    std::cout << "===========================\n";

    for (int t = 0; t < steps; ++t) {
        std::cout << std::setw(3) << t << " | " << std::setw(7) << y_lin[t] << " | " << std::setw(10) << y_non[t] << "\n";
    }
}

int main() {
    run_simulation(25);
    return 0;
}
