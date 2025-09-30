#include <iostream>
#include <vector>
#include <cmath>

// Линейная модель: y[k+1] = alpha * y[k] + beta * u[k]
double modelLinear(double y_curr, double u_curr, double alpha, double beta) {
    return alpha * y_curr + beta * u_curr;
}

// Нелинейная модель:
// y[k+1] = alpha*y[k] - beta*(y[k-1]^2) + gamma*u[k] + delta*sin(u[k-1])
double modelNonlinear(double y_curr, double y_prev, double u_curr, double u_prev,
    double alpha, double beta, double gamma, double delta) {
    return alpha * y_curr - beta * y_prev * y_prev + gamma * u_curr + delta * std::sin(u_prev);
}

int main() {
    const double alpha = 0.9;
    const double beta = 0.15;
    const double gamma = 0.05;
    const double delta = 0.02;

    const int steps = 25;

    std::vector<double> y(steps + 1, 0.0);
    std::vector<double> u(steps + 1, 0.0);

    // Формируем входное воздействие: до шага 7 = 0, затем = 1
    for (int k = 0; k <= steps; ++k) {
        u[k] = (k < 7 ? 0.0 : 1.0);
    }

    std::cout << "=== Linear model ===\n";
    for (int k = 0; k < steps; ++k) {
        y[k + 1] = modelLinear(y[k], u[k], alpha, beta);
        std::cout << "step " << k + 1 << ": y = " << y[k + 1] << "\n";
    }

    std::fill(y.begin(), y.end(), 0.0);

    std::cout << "\n=== Nonlinear model ===\n";
    for (int k = 1; k < steps; ++k) {
        y[k + 1] = modelNonlinear(y[k], y[k - 1], u[k], u[k - 1], alpha, beta, gamma, delta);
        std::cout << "step " << k + 1 << ": y = " << y[k + 1] << "\n";
    }

    return 0;
}
