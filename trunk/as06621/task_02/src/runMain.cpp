#include <iostream>
#include <vector>
#include <iomanip>
#include "func.h"

int main() {
    int steps;
    double y_init;
    double u_const;

    std::cout << "Введите количество шагов моделирования: ";
    std::cin >> steps;
    if (steps <= 0) {
        std::cerr << "Ошибка: число шагов должно быть положительным.\n";
        return 1;
    }

    std::cout << "Введите начальную температуру y0: ";
    std::cin >> y_init;

    std::cout << "Введите постоянное нагревание u: ";
    std::cin >> u_const;

    std::vector<double> y_l(steps + 1, 0.0);
    std::vector<double> y_nl(steps + 1, 0.0);

    y_l[0] = y_init;
    y_nl[0] = y_init;

    for (int t = 0; t < steps; ++t) {

        // Линейная модель
        y_l[t + 1] = linear(y_l[t], u_const);

        // Для нелинейной модели требуется yt, yt-1, ut, ut-1
        double yt      = y_nl[t];          // текущая температура
        double yt_prev = (t > 0 ? y_nl[t - 1] : y_init);  // предыдущая температура
        double ut      = u_const;          // текущий вход
        double ut_prev = (t > 0 ? u_const : ZERO_PREV_INPUT);

        y_nl[t + 1] = nonlinear(yt, yt_prev, ut, ut_prev);
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t\tЛинейная\tНелинейная\n";
    std::cout << "---------------------------------\n";

    for (int t = 0; t <= steps; ++t) {
        std::cout << t << "\t"
                  << std::fixed << std::setprecision(4)
                  << y_l[t] << "\t\t"
                  << y_nl[t] << "\n";
    }

    return 0;
}
