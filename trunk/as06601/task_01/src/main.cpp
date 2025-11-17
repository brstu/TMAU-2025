#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Линейная модель: y[t+1] = a*y[t] + b*u[t]
double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

// Нелинейная модель: y[t+1] = a*y[t] - b*y[t-1]^2 + c*u[t] + d*sin(u[t-1])
double nonlinearModel(double a, double b, double c, double d,
                      double y_t, double y_prev, double u_t, double u_prev) {
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
}

int main() {
    int n;
    cout << "Введите количество шагов моделирования: ";
    cin >> n;

    // Константы (можно менять)
    double a = 0.8, b = 0.1, c = 0.05, d = 0.02;

    // Начальные условия
    double y0 = 20.0;    // начальная температура объекта
    double u0 = 5.0;     // начальное управляющее воздействие

    vector<double> y(n+1);
    vector<double> u(n+1);

    // Заполняем вход (например, постоянное воздействие u = u0)
    for (int t = 0; t <= n; t++) {
        u[t] = u0;
    }

    // Начальные значения температуры
    y[0] = y0;
    if (n > 0) y[1] = y0; // чтобы была "память" для нелинейной модели

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
    if (n > 0) y[1] = y0; // снова задаем старт
    for (int t = 1; t < n; t++) {
        y[t+1] = nonlinearModel(a, b, c, d, y[t], y[t-1], u[t], u[t-1]);
        cout << "t=" << t+1 << "  y=" << y[t+1] << endl;
    }

    return 0;
}
