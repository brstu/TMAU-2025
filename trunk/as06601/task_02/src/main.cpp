#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Нелинейная модель
double nonlinearModel(double a, double b_nl, double c, double d,
                      double y_t, double u_t, double u_prev) {
    return a * y_t - b_nl * y_t * y_t + c * u_t + d * sin(u_prev);
}

// Линейная модель
double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

int main() {
    int n;
    cout << "Введите количество шагов моделирования: ";
    cin >> n;

    if (n <= 0 || n > 1000000) {
        cerr << "Ошибка: n должно быть положительным и не превышать 1,000,000.\n";
        return 1;
    }

    double a = 1.1;
    double b = 0.1;
    double b_nl = 0.0012;
    double c = 0.05;
    double d = 0.02;

    double y0 = 20.0;
    double u0 = 5.0;

    // --- Векторы вместо new/delete ---
    vector<double> y_linear(n + 1);
    vector<double> y_nonlinear(n + 1);
    vector<double> u(n + 1, u0); // сразу заполняем u0

    y_linear[0] = y0;
    y_nonlinear[0] = y0;

    cout << "Результаты моделирования:\n";

    cout << "\n--- Линейная модель ---\n";
    for (int t = 0; t < n; t++) {
        y_linear[t + 1] = linearModel(a, b, y_linear[t], u[t]);
        cout << "t=" << t + 1 << "  y=" << y_linear[t + 1] << '\n';
    }

    cout << "\n--- Нелинейная модель ---\n";
    for (int t = 0; t < n; t++) {
        double u_prev = (t > 0) ? u[t - 1] : u[0];
        y_nonlinear[t + 1] =
            nonlinearModel(a, b_nl, c, d, y_nonlinear[t], u[t], u_prev);
        cout << "t=" << t + 1 << "  y=" << y_nonlinear[t + 1] << '\n';
    }

    return 0;
}