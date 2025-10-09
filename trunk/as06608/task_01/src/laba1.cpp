#include <iostream>
#include <cmath>

int main() {
    // --- Константы модели ---
    constexpr int N = 10;
    constexpr double A = 0.99;
    constexpr double B = 0.01;
    constexpr double C = 0.5;
    constexpr double D = 0.1;
    constexpr double Y0 = 18.0;

    // --- Функции модели ---
    auto linearModel = [](double y, double u) -> double {
        return A * y + B * u;
    };

    auto nonlinearModel = [](double y_now, double y_prev, double u_now, double u_prev) -> double {
        return A * y_now - B * std::pow(y_prev, 2.0) + C * u_now + D * std::sin(u_prev);
    };

    // --- Управляющее воздействие ---
    double u[N] = {5, 7, 6, 5, 7, 6, 5, 7, 6, 5};

    // --- Линейная модель ---
    std::cout << "=== Linear model ===" << std::endl;
    double y_lin = Y0;
    std::cout << "y(0) = " << y_lin << std::endl;

    for (int i = 0; i < N; ++i) {
        y_lin = linearModel(y_lin, u[i]);
        std::cout << "y(" << i + 1 << ") = " << y_lin << std::endl;
    }

    // --- Нелинейная модель ---
    std::cout << "\n=== Nonlinear model ===" << std::endl;
    double y_prev = Y0;
    double y_curr = Y0;
    std::cout << "y(0) = " << y_curr << std::endl;

    for (int i = 0; i < N; ++i) {
        double u_curr = u[i];
        double u_prev = (i == 0) ? u[0] : u[i - 1];

        double y_next = nonlinearModel(y_curr, y_prev, u_curr, u_prev);
        std::cout << "y(" << i + 1 << ") = " << y_next << std::endl;

        y_prev = y_curr;
        y_curr = y_next;
    }

    return 0;
}
