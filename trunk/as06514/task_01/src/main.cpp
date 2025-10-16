#include <iostream>
#include <cmath>      // Для функции sin()
#include <locale>     // Для установки русской локали

using namespace std;

// Функция симуляции линейной модели: yₜ₊₁ = a * yₜ + b * uₜ
void simulateLinearModel(double a, double b, double y0, double u[], int steps) {
    cout << "\nСимуляция линейной модели:\n";
    cout << "Начальная температура (y₀): " << y0 << endl;
    double y = y0;
    for (int t = 0; t < steps; ++t) {
        y = a * y + b * u[t];
        cout << "Шаг " << t + 1 << ": температура = " << y << endl;
    }
}

// Функция симуляции нелинейной модели: yₜ₊₁ = a * yₜ + b * yₜ₋₁ + c * uₜ + d * sin(uₜ₋₁)
void simulateNonlinearModel(double a, double b, double c, double d, double y0, double u[], int steps) {
    cout << "\nСимуляция нелинейной модели:\n";
    cout << "Начальная температура (y₀): " << y0 << endl;
    double y_prev = y0;
    double y = y0;
    for (int t = 0; t < steps; ++t) {
        double u_prev = (t > 0) ? u[t - 1] : 0;
        double y_next = a * y + b * y_prev + c * u[t] + d * sin(u_prev);
        cout << "Шаг " << t + 1 << ": температура = " << y_next << endl;
        y_prev = y;
        y = y_next;
    }
}

int main() {
    // Установка русской локали для корректного отображения текста
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Исходные параметры модели
    double a = 0.8, b = 0.1, c = 0.05, d = 0.02;
    double y0 = 20.0; // Начальная температура
    int steps = 10;   // Количество шагов симуляции

    // Массив значений входного тепла (uₜ)
    double u[] = { 5, 6, 7, 8, 9, 10, 9, 8, 7, 6 };

    // Вызов функций симуляции
    simulateLinearModel(a, b, y0, u, steps);
    simulateNonlinearModel(a, b, c, d, y0, u, steps);

    return 0;
}
