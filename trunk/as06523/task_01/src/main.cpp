#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, double a, double b, double c, double d) {
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
}

int main() {
    int n = 30;
    double a = 0.8, b = 0.15, c = 0.05, d = 0.1;

    std::vector<double> u(n, 1.0);
    std::vector<double> y_lin(n, 0.0);
    std::vector<double> y_nonlin(n, 0.0);

    y_lin[0] = 0.0;
    y_nonlin[0] = 0.0;

    for (int t = 1; t < n; ++t) {
        y_lin[t] = linear_model(y_lin[t-1], u[t-1], a, b);

        if (t > 1) {
            y_nonlin[t] = nonlinear_model(y_nonlin[t-1], y_nonlin[t-2], u[t-1], u[t-2], a, b, c, d);
        } else {
            y_nonlin[t] = linear_model(y_nonlin[t-1], u[t-1], a, b);
        }
    }

    std::cout << "\nStep\tLinear model\tNonlinear model\n";
    for (int t = 0; t < n; ++t) {
        std::cout << t << "\t" << std::fixed << std::setprecision(5) << y_lin[t] << "\t\t" << y_nonlin[t] << "\n";
    }

    return 0;
}
