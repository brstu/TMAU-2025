#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

constexpr double ALPHA = 0.9;
constexpr double BETA = 0.15;
constexpr double GAMMA = 0.05;
constexpr double DELTA = 0.02;

constexpr int STEPS = 25;
constexpr int STEP_THRESHOLD = 7;

// Линейная модель: y[k+1] = α*y[k] + β*u[k]
double linearModel(double yCurr, double uCurr) {
    return ALPHA * yCurr + BETA * uCurr;
}

// Нелинейная модель:
// y[k+1] = α*y[k] - β*(y[k-1]^2) + γ*u[k] + δ*sin(u[k-1])
double nonlinearModel(double yCurr, double yPrev, double uCurr, double uPrev) {
    return ALPHA * yCurr
        - BETA * yPrev * yPrev
        + GAMMA * uCurr
        + DELTA * std::sin(uPrev);
}

void printSimulation(const std::vector<double>& y, const std::string& title) {
    std::cout << title << '\n';
    for (size_t k = 1; k < y.size(); ++k) {
        std::cout << "step " << k << ": y = " << y[k] << '\n';
    }
    std::cout << '\n';
}

int main() {
    std::vector<double> y(STEPS + 1, 0.0);
    std::vector<double> u(STEPS + 1, 0.0);

    // Входное воздействие: до шага 7 = 0, затем = 1
    std::generate(u.begin(), u.end(), [n = 0]() mutable {
        return (n++ < STEP_THRESHOLD) ? 0.0 : 1.0;
        });

    // Линейная модель
    for (int k = 0; k < STEPS; ++k) {
        y[k + 1] = linearModel(y[k], u[k]);
    }
    printSimulation(y, "=== Linear model ===");

    // Обнуляем для нелинейной
    std::fill(y.begin(), y.end(), 0.0);

    // Нелинейная модель
    for (int k = 1; k < STEPS; ++k) {
        y[k + 1] = nonlinearModel(y[k], y[k - 1], u[k], u[k - 1]);
    }
    printSimulation(y, "=== Nonlinear model ===");

    return 0;
}
