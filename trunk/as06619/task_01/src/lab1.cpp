#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double compute_linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

double compute_nonlinear_model(double y_t, double y_prev, 
                               double u_t, double u_prev,
                               double a, double b, double c, double d) {  // Добавил d как параметр
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);  // Используем d вместо 0.05
}

int main() {
    double a = 0.8;
    double b = 0.2;
    double c = 0.1;
    double d = 0.05;  // Теперь эта переменная будет использоваться!

    int N = 20;

    vector<double> y(N + 1, 0.0);
    vector<double> u(N + 1, 0.0);

    for (int t = 0; t <= N; t++) {
        u[t] = (t < 5) ? 0.0 : 1.0;
    }

    cout << "Linear model:" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = compute_linear_model(y[t], u[t], a, b);
        cout << "t = " << t + 1 << "   y = " << y[t + 1] << endl;
    }

    fill(y.begin(), y.end(), 0.0);

    cout << "\nNonlinear model:" << endl;
    for (int t = 1; t < N; t++) {
        y[t + 1] = compute_nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], a, b, c, d);  // Передаем d
        cout << "t = " << t + 1 << "   y = " << y[t + 1] << endl;
    }

    return 0;
}