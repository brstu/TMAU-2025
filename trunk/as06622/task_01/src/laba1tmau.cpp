#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Параметры модели
const int STEPS = 10;
const double K1 = 0.99;
const double K2 = 0.01;
const double K3 = 0.5;
const double K4 = 0.1;
const double Y0 = 18.0;

// Линейная динамика
double linModel(double y, double u) {
    return K1 * y + K2 * u;
}

// Нелинейная динамика
double nonlinEq(double y, double y_prev, double u, double u_prev) {
    return K1 * y + K3 * u - K2 * pow(y_prev, 2) + K4 * sin(u_prev);
}

void simulateLinear(const vector<double>& input) {
    double y = Y0;
    cout << "=== Линейная модель ===" << endl;
    cout << "y0 = " << Y0 << endl;
    for (int i = 0; i < STEPS; i++) {
        y = linModel(y, input[i]);
        cout << "Шаг " << i + 1 << ": y = " << y << endl;
    }
}

void simulateNonlinear(const vector<double>& input) {
    double y = Y0;
    double y_prev = Y0;
    cout << "\n=== Нелинейная модель ===" << endl;
    cout << "y0 = " << Y0 << endl;
    for (int i = 0; i < STEPS; i++) {
        double u_prev = (i == 0) ? input[0] : input[i - 1];
        y = nonlinEq(y, y_prev, input[i], u_prev);
        cout << "Шаг " << i + 1 << ": y = " << y << endl;
        y_prev = y;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Initialize input vector with STEPS elements, e.g., repeating pattern 5,7,6
    vector<double> input;
    for (int i = 0; i < STEPS; ++i) {
        switch (i % 3) {
            case 0: input.push_back(5); break;
            case 1: input.push_back(7); break;
            case 2: input.push_back(6); break;
            default: input.push_back(0); break; // Handles unexpected values
        }
    }
    // Optional: runtime check
    if (input.size() != STEPS) {
        cerr << "Ошибка: размер входного вектора не совпадает с STEPS." << endl;
        return 1;
    }
    simulateLinear(input);
    simulateNonlinear(input);
    return 0;
}