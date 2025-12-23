#include <iostream>
#include <vector>
#include <iomanip>
#include "func.h"

int main() {
    int n;
    double y0;
    double u_val;

    std::cout << "Введите количество шагов n: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Ошибка: число шагов должно быть положительным.\n";
        return 1;
    }

    std::cout << "Введите начальное значение температуры y0: ";
    std::cin >> y0;

    std::cout << "Введите постоянное воздействие (нагрев) u: ";
    std::cin >> u_val;

    std::vector<double> y_lin(n + 1, 0.0);
    std::vector<double> y_nonlin(n + 1, 0.0);
    std::vector<double> u(n + 1, u_val);

    y_lin[0] = y0;
    y_nonlin[0] = y0;

    for (int t = 0; t < n; ++t) {
        double prev_u = (t > 0) ? u[t - 1] : INITIAL_PREV_U;

        y_lin[t + 1] = linear_step(y_lin[t], u[t]);
        y_nonlin[t + 1] = nonlinear_step(y_nonlin[t], u[t], prev_u);
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "Шаг\tЛинейная\tНелинейная\n";
    std::cout << "---------------------------------\n";

    for (int t = 0; t <= n; ++t) {
        std::cout << t << "\t"
                  << std::fixed << std::setprecision(4)
                  << y_lin[t] << "\t\t" << y_nonlin[t] << "\n";
    }

    return 0;
}
