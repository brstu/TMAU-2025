#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct NonlinearParams {
    double y_t;
    double y_prev;
    double u_t;
    double u_prev;
    double a;
    double b;
    double c;
    double d;
};

double compute_linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

double compute_nonlinear_model(const NonlinearParams& p) {
    return p.a * p.y_t - p.b * p.y_prev * p.y_prev + p.c * p.u_t + p.d * sin(p.u_prev);
}

int main() {
    double a = 0.8;
    double b = 0.2;
    double c = 0.1;
    double d = 0.05;

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
        NonlinearParams p;
        p.y_t = y[t];
        p.y_prev = y[t - 1];
        p.u_t = u[t];
        p.u_prev = u[t - 1];
        p.a = a;
        p.b = b;
        p.c = c;
        p.d = d;

        y[t + 1] = compute_nonlinear_model(p);
        cout << "t = " << t + 1 << "   y = " << y[t + 1] << endl;
    }

    return 0;
}
