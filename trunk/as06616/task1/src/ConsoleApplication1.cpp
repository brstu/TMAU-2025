#include <iostream>
#include <cmath>

const double temperatureCoeff = 0.6;
const double prevTemperatureCoeff = 0.3;
const double warmCoeff = 0.8;
const double prevWarmCoeffSin = 0.5;

double updateWarm(double warm, int t);

double linearmodel(double inputtemperature, double inputwarm) {
    return temperatureCoeff * inputtemperature + prevTemperatureCoeff * inputwarm;
}

double nonlinearmodel(double inputtemperature, double prevtemperature, double inputwarm, double prevwarm) {
    return temperatureCoeff * inputtemperature - prevTemperatureCoeff * pow(prevtemperature, 2) + warmCoeff * inputwarm + prevWarmCoeffSin * sin(prevwarm);
}

double updateWarm(double baseWarm, int t) {
    return baseWarm + 0.1 * sin(t);
}

int main() {
    
    int time;
    double inputtemperature;
    double inputwarm;
    
    std::cout << "Введите количество шагов моделирования, начальную температуру y0 и начальный тепловой вход u0: ";
    std::cin >> time >> inputtemperature >> inputwarm;

    double prevtemperature = inputtemperature;
    double prevwarm = inputwarm;

    std::cout << "\nМоделирование линейной модели:\n";
    double y_linear = inputtemperature;
    for (int t = 1; t <= time; t++) {
        y_linear = linearmodel(y_linear, inputwarm);
        std::cout << "Шаг " << t << ": y = " << y_linear << std::endl;
    }

    std::cout << "\nМоделирование нелинейной модели:\n";
    double y_nl = inputtemperature;
    for (int t = 1; t <= time; t++) {
        double currentWarm = updateWarm(inputwarm, t);
        double next = nonlinearmodel(y_nl, prevtemperature, currentWarm, prevwarm);
        std::cout << "Шаг " << t << ": y = " << next << std::endl;
        prevtemperature = y_nl;
        y_nl = next;
        prevwarm = currentWarm;
    }

    return 0;
}
