#include <iostream>
#include <vector>
#include "model_functions.h"

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    if (!setlocale(LC_ALL, "ru_RU.UTF-8")) {
        std::cerr << "Warning: Не удалось установить русскую локаль. Вывод может отображаться некорректно." << std::endl;
    }

    double temperatureInitial = 20.0;

    std::vector<double> inputs = {
        15.0, 16.5, 18.0, 20.0, 22.5, 25.0, 24.0, 21.0, 18.0, 16.0
    };

    std::cout << "Линейная модель\nНачальное значение: " << temperatureInitial << "\n";

    double prevTemperature = temperatureInitial;
    for (size_t t = 0; t < inputs.size(); ++t) {
        double newTemperature = calcLinear(prevTemperature, inputs[t]);
        std::cout << "y[" << t + 1 << "] = " << newTemperature << std::endl;
        prevTemperature = newTemperature;
    }

    std::cout << "\nНелинейная модель\nНачальное значение: " << temperatureInitial << "\n";

    double currentY = temperatureInitial;
    double previousY = temperatureInitial;

    for (size_t t = 1; t < inputs.size(); ++t) {
        double uCurr = inputs[t];
        double uPrev = inputs[t - 1];

        double newY = calcNonlinear(currentY, previousY, uCurr, uPrev);
        std::cout << "y[" << t << "] = " << newY << std::endl;

        previousY = currentY;
        currentY = newY;
    }

    std::cout << "Press Enter to continue...";
    std::cin.get();

    return 0;
}