#include <iostream>
#include <vector>
#include <cmath>

const int STEPS = 10;
const double K1 = 0.98;
const double K2 = 0.03;
const double K3 = 0.4;
const double K4 = 0.2;
const double Y0 = 19.0;

double linModel(double y, double u) {
    return K1 * y + K2 * u;
}

double nonlinEq(double y, double y_prev, double u, double u_prev) {
    return K1 * y + K3 * u - K2 * std::pow(y_prev, 2) + K4 * std::sin(u_prev);
}

void simulateLinear(const std::vector<double>& input) {
    double y = Y0;
    std::cout << "=== Линейная модель ===" << std::endl;
    std::cout << "y0 = " << Y0 << std::endl;
    for (int i = 0; i < STEPS; i++) {
        y = linModel(y, input[i]);
        std::cout << "Шаг " << i + 1 << ": y = " << y << std::endl;
    }
}

void simulateNonlinear(const std::vector<double>& input) {
    double y = Y0, y_prev = Y0;
    std::cout << "\n=== Нелинейная модель ===" << std::endl;
    std::cout << "y0 = " << Y0 << std::endl;
    for (int i = 1; i < STEPS; i++) {
        y = nonlinEq(y, y_prev, input[i], input[i - 1]);
        std::cout << "Шаг " << i << ": y = " << y << std::endl;
        y_prev = y;
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::vector<double> input = { 5,7,6,5,7,6,5,7,6,5 };
    simulateLinear(input);
    simulateNonlinear(input);
    return 0;
}