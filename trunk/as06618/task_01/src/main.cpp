#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    // Коэффициенты линейной динамики
    double k1 = 0.8;
    double k2 = 0.2;

    // Коэффициенты нелинейной системы
    double p1 = 0.7;
    double p2 = 0.005;
    double p3 = 0.25;
    double p4 = 0.1;

    // Состояния в начальный момент
    double temp_lin = 20.0;
    double temp_nonlin = 20.0;

    // Управляющее воздействие
    double control = 1.0;
    double prev_control = control;

    const int steps = 30;

    std::cout << "Эволюция температурных моделей\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::setw(6) << "t"
              << std::setw(14) << "Linear"
              << std::setw(14) << "Nonlinear"
              << std::setw(14) << "Control" << "\n";

    for (int t = 0; t < steps; t++) {

        // Вывод текущего состояния
        std::cout << std::setw(6) << t
                  << std::setw(14) << std::fixed << std::setprecision(2) << temp_lin
                  << std::setw(14) << temp_nonlin
                  << std::setw(14) << control << "\n";

        // Расчёт следующих состояний
        double next_lin = k1 * temp_lin + k2 * control;

        double next_nonlin =
                p1 * temp_nonlin
                - p2 * temp_nonlin * temp_nonlin
                + p3 * control
                + p4 * std::sin(prev_control - 1.0);

        // Обновление
        temp_lin = next_lin;
        temp_nonlin = next_nonlin;
        prev_control = control;

        // Простое управление
        if (temp_lin < 18.0) {
            control = 1.5;
        } else if (temp_lin > 28.0) {
            control = 0.0;
        } else {
            control = 1.0;
        }
    }

    return 0;
}
