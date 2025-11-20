#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Функция для линейной модели
double computeLinear(double current_y, double current_u, double factor_a, double factor_b) {
    return factor_a * current_y + factor_b * current_u;
}

// Функция для нелинейной модели
double computeNonlinear(double current_y, double previous_y, double current_u, double previous_u,
    double factor_a, double factor_b, double factor_c, double factor_d) {
    return factor_a * current_y - factor_b * previous_y * previous_y + factor_c * current_u + factor_d * sin(previous_u);
}

int main() {
    const double factor_a = 0.6; 
    const double factor_b = 0.3;
    const double factor_c = 0.15; 
    const double factor_d = 0.08; 

    const int steps = 20;

    vector<double> temperature(steps + 1, 0.0); // Вектор для температуры
    vector<double> input(steps + 1, 0.0); // Вектор для входных значений

    // Инициализация входных значений
    for (int time = 0; time <= steps; ++time) {
        input[time] = (time < 5) ? 0.0 : 1.0; // Установка значений на основе времени
    }

    cout << "Results of the Linear Model:" << endl;
    // Вычисление линейной модели
    for (int time = 0; time < steps; ++time) {
        temperature[time + 1] = computeLinear(temperature[time], input[time], factor_a, factor_b);
        cout << "Time=" << time + 1 << "  Temperature=" << temperature[time + 1] << endl;
    }

    fill(temperature.begin(), temperature.end(), 0.0); // Очистка вектора температуры для следующей модели

    cout << "\nResults of the Nonlinear Model:" << endl;
    // Вычисление нелинейной модели
    for (int time = 1; time < steps; ++time) {
        temperature[time + 1] = computeNonlinear(temperature[time], temperature[time - 1], input[time], input[time - 1],
            factor_a, factor_b, factor_c, factor_d);
        cout << "Time=" << time + 1 << "  Temperature=" << temperature[time + 1] << endl;
    }

    return 0;
}
