#include <iostream>
#include <vector>
#include <iomanip>
#include "func.h"

int main() {
    using namespace TemperatureModels;
    using namespace ModelConstants;
    
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

    std::vector<double> y_linear(steps + 1, 0.0);
    std::vector<double> y_nonlinear(steps + 1, 0.0);

    y_linear[0] = y_init;
    y_nonlinear[0] = y_init;

    for (int t = 0; t < steps; ++t) {
        // Линейная модель
        y_linear[t + 1] = computeLinearModel(y_linear[t], u_const);

        // Для нелинейной модели требуются yt, yt-1, ut, ut-1
        double current_temperature = y_nonlinear[t];
        double previous_temperature = (t > 0 ? y_nonlinear[t - 1] : y_init);
        double current_control = u_const;
        double previous_control = (t > 0 ? u_const : ZERO_PREV_INPUT);

        y_nonlinear[t + 1] = computeNonlinearModel(
            current_temperature,
            previous_temperature,
            current_control,
            previous_control
        );
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t\tЛинейная\tНелинейная\n";
    std::cout << "---------------------------------\n";

    for (int t = 0; t <= steps; ++t) {
        std::cout << t << "\t"
                  << std::fixed << std::setprecision(4)
                  << y_linear[t] << "\t\t"
                  << y_nonlinear[t] << "\n";
    }

    return 0;
}