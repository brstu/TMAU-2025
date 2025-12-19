#include <iostream>
#include <vector>
#include <numeric>   // std::iota
#include "func.h"

using std::cout;
using std::endl;
using std::vector;

// Можно явно импортировать функции из namespace, чтобы не писать Model::
using Model::linearModel;
using Model::nonlinearModel;

static void runLinear(const vector<double>& input) {
    double y = Y0;
    cout << "=== Симуляция линейной модели ===\n";
    cout << "y0 = " << Y0 << '\n';
    for (int step = 0; step < STEPS; ++step) {
        y = linearModel(y, input[step]);
        cout << "[Линейный шаг " << step + 1 << "] y = " << y << '\n';
    }
}

static void runNonlinear(const vector<double>& input) {
    double y = Y0;
    double y_prev = Y0;
    cout << "\n=== Симуляция нелинейной модели ===\n";
    cout << "y0 = " << Y0 << '\n';
    for (int step = 0; step < STEPS; ++step) {
        const double u_prev = (step == 0) ? input[0] : input[step - 1];
        y = nonlinearModel(y, y_prev, input[step], u_prev);
        cout << "[Нелинейный шаг " << step + 1 << "] y = " << y << '\n';
        y_prev = y;
    }
}

int main() {
    // Генерация входной последовательности: 1, 2, ..., STEPS
    vector<double> input(STEPS);
    std::iota(input.begin(), input.end(), 1.0);

    runLinear(input);
    runNonlinear(input);
    return 0;
}
