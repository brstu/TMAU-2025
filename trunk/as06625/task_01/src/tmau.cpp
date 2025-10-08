#include <iostream>
#include <cmath>
#include <vector>
using std::cout;
using std::endl;

// Константы
const int TIME_STEPS = 10; // количество временных шагов
const double COEFF_A = 0.99;
const double COEFF_B = 0.01;
const double COEFF_C = 0.5;
const double COEFF_D = 0.1;
const double INITIAL_Y = 18;
const double initial_u = 0.0;

// Линейная модель
double compute_linear(double current_y, double input_u) {
    return COEFF_A * current_y + COEFF_B * input_u;
}

// Нелинейная модель
double compute_nonlinear(double current_y, double previous_y, double input_u, double previous_u) {
    return COEFF_A * current_y - COEFF_B * pow(previous_y, 2) + COEFF_C * input_u + COEFF_D * sin(previous_u);
}

int main() {
    cout << "Линейная модель" << endl;
    cout << "y0 = " << INITIAL_Y << endl;
    // Вектор входных значений (inputs) моделирует подачу тепла на каждом временном шаге.
    // Значения выбраны для демонстрации работы модели с переменным тепловым воздействием.
    std::vector<double> inputs = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
    double current_y = INITIAL_Y;

    for (int i = 0; i < TIME_STEPS; i++) {
        current_y = compute_linear(current_y, inputs[i]);
        cout << "y" << i + 1 << " = " << current_y << endl;
    }

    cout << "\n";

    double previous_y = INITIAL_Y;
    current_y = INITIAL_Y;

    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << INITIAL_Y << endl;

    for (int i = 0; i < TIME_STEPS; i++) {
        double current_u = inputs[i];
        double previous_u = (i == 0) ? initial_u : inputs[i - 1]; // безопасное начальное значение

        double new_y = compute_nonlinear(current_y, previous_y, current_u, previous_u);
        cout << "y" << i + 1 << " = " << new_y << endl;

        previous_y = current_y;
        current_y = new_y;
    }

    return 0;
}
