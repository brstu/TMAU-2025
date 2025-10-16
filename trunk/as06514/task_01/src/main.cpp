#include <iostream>
#include <cmath>      // Для функции sin()
#include <locale>     // Для установки русской локали

using namespace std;

// Функция симуляции линейной модели: temp_next = coeffA * temp_curr + coeffB * heat_input
void simulateLinearModel(double coeffA, double coeffB, double initialTemp, double heatFlow[], int totalSteps) {
    cout << "\nСимуляция линейной модели:\n";
    cout << "Начальная температура: " << initialTemp << endl;
    double currentTemp = initialTemp;
    for (int step = 0; step < totalSteps; ++step) {
        currentTemp = coeffA * currentTemp + coeffB * heatFlow[step];
        cout << "Шаг " << step + 1 << ": температура = " << currentTemp << endl;
    }
}

// Функция симуляции нелинейной модели: temp_next = coeffA * temp_curr + coeffB * temp_prev + coeffC * heat_input + coeffD * sin(prev_heat_input)
void simulateNonlinearModel(double coeffA, double coeffB, double coeffC, double coeffD, double initialTemp, double heatFlow[], int totalSteps) {
    cout << "\nСимуляция нелинейной модели:\n";
    cout << "Начальная температура: " << initialTemp << endl;
    double previousTemp = initialTemp;
    double currentTemp = initialTemp;
    for (int step = 0; step < totalSteps; ++step) {
        double previousHeat = (step > 0) ? heatFlow[step - 1] : 0;
        double nextTemp = coeffA * currentTemp + coeffB * previousTemp + coeffC * heatFlow[step] + coeffD * sin(previousHeat);
        cout << "Шаг " << step + 1 << ": температура = " << nextTemp << endl;
        previousTemp = currentTemp;
        currentTemp = nextTemp;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Параметры модели
    double coeffA = 0.8, coeffB = 0.1, coeffC = 0.05, coeffD = 0.02;
    double initialTemp = 20.0;
    int totalSteps = 10;

    // Массив входного тепла
    double heatFlow[] = { 3, 4, 5, 6, 7, 8, 9, 10, 9, 8 };

    // Запуск симуляций
    simulateLinearModel(coeffA, coeffB, initialTemp, heatFlow, totalSteps);
    simulateNonlinearModel(coeffA, coeffB, coeffC, coeffD, initialTemp, heatFlow, totalSteps);

    return 0;
}
