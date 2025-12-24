#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Параметры нелинейной модели
struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

// Состояние (выходы и входы)
struct State {
    double y_t;
    double y_prev;
    double u_t;
    double u_prev;
};

// Линейная модель: y[t+1] = a*y[t] + b*u[t]
double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

// Нелинейная модель
double nonlinearModel(const NonlinearParams& p, const State& s) {
    return p.a * s.y_t
         - p.b * s.y_prev * s.y_prev
         + p.c * s.u_t
         + p.d * sin(s.u_prev);
}

int main() {
    int n;
    cout << "Введите количество шагов моделирования: ";
    cin >> n;

    // Константы (разделены по требованиям Sonar)
    double a = 0.8;
    double b = 0.1;
    double c = 0.05;
    double d = 0.02;

    NonlinearParams params{a, b, c, d};

    // Начальные условия
    double y0 = 20.0; // начальная температура объекта
    double u0 = 5.0;  // начальное управляющее воздействие

    vector<double> y(n+1);
    vector<double> u(n+1);

    // Вход
    for (int t = 0; t <= n; t++) {
        u[t] = u0;
    }

    y[0] = y0;
    if (n > 0) y[1] = y0;

    cout << "Результаты моделирования:\n";

    // Линейная модель
    cout << "\n--- Линейная модель ---\n";
    for (int t = 0; t < n; t++) {
        y[t+1] = linearModel(a, b, y[t], u[t]);
        cout << "t=" << t+1 << "  y=" << y[t+1] << endl;
    }

    // Нелинейная модель
    cout << "\n--- Нелинейная модель ---\n";
    y[0] = y0;
    if (n > 0) y[1] = y0;

    for (int t = 1; t < n; t++) {
        State st{y[t], y[t-1], u[t], u[t-1]};
        y[t+1] = nonlinearModel(params, st);
        cout << "t=" << t+1 << "  y=" << y[t+1] << endl;
    }

    return 0;
}
