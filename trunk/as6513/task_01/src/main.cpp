#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Линейная модель
double linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

// Нелинейная модель
double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev,
                       double a, double b, double c, double d) {
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
}

int main() {
    // Константы модели
    double a = 0.8;
    double b = 0.2;
    double c = 0.1;
    double d = 0.05;

    int N = 20; // количество шагов моделирования

    vector<double> y(N + 1, 0.0);
    vector<double> u(N + 1, 0.0);

    // Задаём входной сигнал u[t]: первые 5 шагов = 0, потом = 1
    for (int t = 0; t <= N; t++) {
        if (t < 5) u[t] = 0.0;
        else u[t] = 1.0;
    }

    cout << "=== Linear model ===" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], a, b);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    // Сброс вектора y для нелинейной модели
    fill(y.begin(), y.end(), 0.0);

    cout << "\n=== Nonlinear model ===" << endl;
    for (int t = 1; t < N; t++) {
        y[t + 1] = nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], a, b, c, d);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    return 0;
}
