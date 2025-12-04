#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>
#include <vector>
#include "func.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    array<double, N> u = { 2.0, 4.0, 3.0, 5.0, 4.0, 6.0, 3.0, 5.0 };

    cout << fixed << setprecision(4);

    cout << "=== МОДЕЛЬ 1 — Линейная ===" << endl;
    cout << "y0 = " << start_value << endl;

    double y = start_value;
    for (int i = 0; i < N; i++) {
        y = linear(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\n=== Нелинейная модель ===" << endl;
    cout << "y0 = " << start_value << endl;

    vector<double> results = { start_value };

    for (int i = 0; i < N - 1; i++) {
        double y_next = nonlinear(results[i],
                                  (i > 0 ? results[i - 1] : start_value),
                                  u[i],
                                  u[i]);
        results.push_back(y_next);
        cout << "y" << i + 1 << " = " << y_next << endl;
    }

    cout << "\nРасчет завершен." << endl;
    return 0;
}
