#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Структура для хранения коэффициентов модели
struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

double linear_model(double y_t, double u_t, const ModelParams& params) {
    return params.a * y_t + params.b * u_t;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev,
    const ModelParams& params) {
    return params.a * y_t
        - params.b * y_prev * y_prev
        + params.c * u_t
        + params.d * sin(u_prev);
}

int main() {
    ModelParams params{ 0.8, 0.2, 0.1, 0.05 };

    int N = 20;

    vector<double> y(N + 1, 0.0);
    vector<double> u(N + 1, 0.0);

    for (int t = 0; t <= N; t++) {
        if (t < 5) u[t] = 0.0;
        else u[t] = 1.0;
    }

    cout << "linear model" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], params);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    fill(y.begin(), y.end(), 0.0);

    cout << "\nnon linear model" << endl;
    for (int t = 1; t < N; t++) {
        y[t + 1] = nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], params);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    return 0;
}

