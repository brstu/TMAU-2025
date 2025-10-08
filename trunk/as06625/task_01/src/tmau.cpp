#include <iostream>
#include <cmath>
#include <vector>
using std::cout;
using std::endl;

// Константы
constexpr int TIME_STEPS = 10;        // количество временных шагов
constexpr double COEFF_A = 0.99;
constexpr double COEFF_B = 0.01;
constexpr double COEFF_C = 0.5;
constexpr double COEFF_D = 0.1;
constexpr double INITIAL_Y = 18;

// Входные значения вынесены в константу для удобства и поддерживаемости
const std::vector<double> INPUTS = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };

// Линейная модель
double compute_linear(double current_y, double input_u) {
    return COEFF_A * current_y + COEFF_B * input_u;
}

// Нелинейная модель
double compute_nonlinear(double current_y, double previous_y, double input_u, double previous_u) {
    return COEFF_A * current_y - COEFF_B * pow(previous_y, 2) + COEFF_C * input_u + COEFF_D * sin(previous_u);
}

int main() {
    // ----------------- Линейная модель -----------------
    cout << "Линейная модель" << endl;
    cout << "y0 = " << INITIAL_Y << endl;

    // Вектор входных значений (inputs) моделирует подачу тепла на каждом временном шаге.
    // Значения выбраны для демонстрации работы модели с переменным тепловым воздействием.
    double current_y = INITIAL_Y;

    for (int i = 0; i < TIME_STEPS; i++) {
        current_y = compute_linear(current_y, INPUTS[i]);
        cout << "y" << i + 1 << " = " << current_y << endl;
    }

    cout << "\n";

    // ----------------- Нелинейная модель -----------------
    double previous_y = INITIAL_Y;
    current_y = INITIAL_Y;

    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << INITIAL_Y << endl;

    for (int i = 0; i < TIME_STEPS; i++) {
        double current_u = INPUTS[i];
        double previous_u = (i == 0) ? INPUTS[0] : INPUTS[i - 1]; // первый previous_u равен INPUTS[0]

        double new_y = compute_nonlinear(current_y, previous_y, current_u, previous_u);
        cout << "y" << i + 1 << " = " << new_y << endl;

        previous_y = current_y;
        current_y = new_y;
    }

    return 0;
}