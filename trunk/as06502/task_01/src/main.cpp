#include <iostream>
#include <cmath>
#include <vector>

namespace Constants {
    const double A = 0.2;
    const double B = 0.02;
    const double C = 0.03;
    const double D = 0.04;
}

double calcLinear(double currentY, double inputU) {
    return (Constants::A * currentY) + (Constants::B * inputU);
}

double calcNonlinear(double currentY, double prevY, double inputU, double prevU) {
    return (Constants::A * currentY) - (Constants::B * prevY * prevY) + (Constants::C * inputU) + Constants::D * sin(prevU);
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    if (!setlocale(LC_ALL, "ru_RU.UTF-8")) {
        std::cerr << "Warning: Unable to set Russian locale. Output may not display correctly." << std::endl;
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

    for (size_t t = 0; t < inputs.size(); ++t) {
        double uCurr = inputs[t];
        double uPrev = (t == 0) ? inputs[0] : inputs[t-1];
        double newY = calcNonlinear(currentY, previousY, uCurr, uPrev);
        std::cout << "y[" << t + 1 << "] = " << newY << std::endl;
    }

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}