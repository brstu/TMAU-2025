#include <iostream>
#include <vector>
#include "model.h"

int main() {
    double a = 0.8;
    double b = 0.2;
    double c = 0.1;
    double d = 0.05;
    int N = 20;

    std::vector<double> y(N + 1, 0.0);
    std::vector<double> u(N + 1, 0.0);

    for (int t = 0; t <= N; t++) {
        u[t] = (t < 5) ? 0.0 : 1.0;
    }

    std::cout << "Linear model:\n";
    for (int t = 0; t < N; t++) {
        y[t + 1] = compute_linear_model(y[t], u[t], a, b);
        std::cout << "t = " << t + 1 << "   y = " << y[t + 1] << std::endl;
    }

    std::fill(y.begin(), y.end(), 0.0);

    std::cout << "\nNonlinear model:\n";
    for (int t = 1; t < N; t++) {
        NonlinearParams p;
        p.y_curr = y[t];
        p.y_prev = y[t - 1];
        p.u_curr = u[t];
        p.u_prev = u[t - 1];
        p.a = a;
        p.b = b;
        p.c = c;
        p.d = d;

        y[t + 1] = compute_nonlinear_model(p);
        std::cout << "t = " << t + 1 << "   y = " << y[t + 1] << std::endl;
    }

    return 0;
}
