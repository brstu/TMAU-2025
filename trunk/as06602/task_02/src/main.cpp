#include <iostream>
#include <vector>
#include <cmath>
#include "model.h"

using namespace std;

int main() {
    int n;
    cout << "Введите количество шагов моделирования: ";
    cin >> n;

    if (n <= 0 || n > 1000000) {
        cerr << "Ошибка: n должно быть положительным и не превышать 1,000,000.\n";
        return 1;
    }

    const double A = 0.8;
    const double B = 0.1;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;

    const double Y0 = 20.0;
    const double U0 = 5.0;

    vector<double> y_linear = simulateLinear(n, A, B, Y0, U0);
    vector<double> y_nonlinear = simulateNonlinear(n, A, B_NL, C, D, Y0, U0);

    cout << "Результаты моделирования:\n";

    cout << "\n--- Линейная модель ---\n";
    for (int t = 1; t <= n; t++) {
        cout << "t=" << t << "  y=" << y_linear[t] << '\n';
    }

    cout << "\n--- Нелинейная модель ---\n";
    for (int t = 1; t <= n; t++) {
        cout << "t=" << t << "  y=" << y_nonlinear[t] << '\n';
    }

    return 0;
}