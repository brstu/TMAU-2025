#include <iostream>
#include <vector>
#include <cmath>

const int STEPS = 10;
const double K1 = 0.98;
const double K2 = 0.03;
const double K3 = 0.4;
const double K2_NONLIN = 0.02;  // Изменил название, чтобы избежать конфликта
const double K4 = 0.2;
const double Y0 = 19.0;

double linModel(double y, double u) {
    return K1 * y + K2 * u;
}

double nonlinModel(double y_prev, double u, double u_prev) {
    return K1 * y_prev - K2_NONLIN * std::pow(y_prev, 2) + K3 * u + K4 * std::sin(u_prev);
}

void simulateLinear(const std::vector<double>& input) {
    double y = Y0;
    std::cout << "=== Линейная модель ===" << std::endl;
    std::cout << "y0 = " << Y0 << std::endl;
    for (int i = 0; i < STEPS; i++) {
        y = linModel(y, input[i]);
        std::cout << "Шаг " << i + 1 << ": y = " << y << ", u = " << input[i] << std::endl;
    }
}

void simulateNonlinear(const std::vector<double>& input) {
    double y = Y0;
    std::cout << "\n=== Нелинейная модель ===" << std::endl;
    std::cout << "y0 = " << Y0 << std::endl;

    // Первый шаг - используем начальное значение
    double y_next = nonlinModel(y, input[0], input[0]); // для первого шага u_prev = u
    std::cout << "Шаг 1: y = " << y_next << ", u = " << input[0] << std::endl;

    // Последующие шаги
    for (int i = 1; i < STEPS; i++) {
        y = y_next;
        y_next = nonlinModel(y, input[i], input[i - 1]);
        std::cout << "Шаг " << i + 1 << ": y = " << y_next << ", u = " << input[i] << ", u_prev = " << input[i - 1] << std::endl;
    }
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::vector<double> input = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };

    simulateLinear(input);
    simulateNonlinear(input);

    return 0;
}