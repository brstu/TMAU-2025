#include <iostream>
#include <vector>
#include "func.h"

using namespace std;

// Линейная модель
static void runLinear(const vector<double>& input) {
    double y = Y0;
    cout << "=== Симуляция линейной модели ===\n";
    cout << "Начальное значение y0 = " << Y0 << '\n';
    for (int i = 0; i < STEPS; ++i) {
        y = linearModel(y, input[i]);
        cout << "[Линейный шаг " << i + 1 << "] y = " << y << '\n';
    }
}

// Нелинейная модель
static void runNonlinear(const vector<double>& input) {
    double y = Y0;
    double y_prev = Y0;
    cout << "\n=== Симуляция нелинейной модели ===\n";
    cout << "Начальное значение y0 = " << Y0 << '\n';
    for (int i = 0; i < STEPS; ++i) {
        double u_prev = (i == 0) ? input[0] : input[i - 1];
        y = nonlinearModel(y, y_prev, input[i], u_prev);
        cout << "[Нелинейный шаг " << i + 1 << "] y = " << y << '\n';
        y_prev = y;
    }
}

int main() {
    // Входная последовательность (шаблон)
    vector<double> input;
    vector<double> pattern = {5, 7, 0};
    for (int i = 0; i < STEPS; ++i) {
        input.push_back(pattern[i % pattern.size()]);
    }

    runLinear(input);
    runNonlinear(input);
    return 0;
}
