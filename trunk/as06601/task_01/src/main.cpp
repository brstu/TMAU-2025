#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Структура для хранения параметров модели
struct Params {
    double a;
    double b_nl;
    double c;
    double d;
};

// Структура для хранения текущих и предыдущих значений
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

// Нелинейная модель: y[t+1] = a*y[t] - b_nl*y[t-1]^2 + c*u[t] + d*sin(u[t-1])
double nonlinearModel(const Params& p, const State& s) {
    return p.a * s.y_t - p.b_nl * s.y_prev * s.y_prev + p.c * s.u_t + p.d * sin(s.u_prev);
}

int main() {
    int n;
    cout << "Введите количество шагов моделирования: ";
    cin >> n;

    // Константы (можно менять)
    double a = 0.8;
    double b = 0.1;      // для линейной модели
    double b_nl = 0.12;  // для нелинейной модели (может отличаться)
    double c = 0.05;
    double d = 0.02;

    // Начальные условия
    double y0 = 20.0;    // начальная температура объекта
    double u0 = 5.0;     // начальное управляющее воздействие

    vector<double> y_linear(n + 1);
    vector<double> y_nonlinear(n + 1);
    vector<double> u(n + 1);

    // Заполняем вход (например, постоянное воздействие u = u0)
    for (int t = 0; t <= n; t++) {
        u[t] = u0;
    }

    // Начальные значения
    y_linear[0] = y0;
    y_nonlinear[0] = y0;
    if (n > 0) {
        y_linear[1] = y0;
        y_nonlinear[1] = y0;
    }

    cout << "Результаты моделирования:\n";

    // --- Линейная модель ---
    cout << "\n--- Линейная модель ---\n";
    for (int t = 0; t < n; t++) {
        y_linear[t + 1] = linearModel(a, b, y_linear[t], u[t]);
        cout << "t=" << t + 1 << "  y=" << y_linear[t + 1] << endl;
    }

    // --- Нелинейная модель ---
    cout << "\n--- Нелинейная модель ---\n";
    Params params = {a, b_nl, c, d};
    State state;

    for (int t = 0; t < n; t++) { // исправлено: теперь t = 0
        double y_prev = (t > 0) ? y_nonlinear[t - 1] : y_nonlinear[0];
        double u_prev = (t > 0) ? u[t - 1] : u[0];
        state = {y_nonlinear[t], y_prev, u[t], u_prev};
        y_nonlinear[t + 1] = nonlinearModel(params, state);
        cout << "t=" << t + 1 << "  y=" << y_nonlinear[t + 1] << endl;
    }

    return 0;
}
