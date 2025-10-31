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
    for (int i = 1; i < STEPS; i++) {
        y = nonlinEq(y, y_prev, input[i], input[i - 1]);
        cout << "Шаг " << i << ": y = " << y << endl;
        y_prev = y;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<double> input = { 5,7,6,5,7,6,5,7,6,5 };
    simulateLinear(input);
    simulateNonlinear(input);
    return 0;
}