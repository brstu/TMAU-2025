#include <iostream>
#include <vector>
#include <cmath>

namespace model {
    const double a = 0.99;
    const double b = 0.01;
    const double c = 0.5;
    const double d = 0.1;

    double linear(double y, double u) {
        return a * y + b * u;
    }

    double nonlinear(double y, double y_prev, double u, double u_prev) {
        return a * y - b * std::pow(y_prev, 2) + c * u + d * std::sin(u_prev);
    }
}

int main() {
    const int steps = 10;
    const double Y0 = 18.0;

    std::vector<double> inputs = {5,7,6,5,7,6,5,7,6,5};

    std::cout << "Linear model\n";
    double y_lin = Y0;
    for (int i = 0; i < steps; ++i) {
        y_lin = model::linear(y_lin, inputs[i]);
        std::cout << "y" << i+1 << " = " << y_lin << "\n";
    }

    std::cout << "\nNonlinear model\n";
    double y_prev = Y0;
    double y_nonlin = Y0;
    for (int i = 0; i < steps; ++i) {
        double u = inputs[i];
        double u_prev = (i == 0) ? inputs[0] : inputs[i-1];
        double y_new = model::nonlinear(y_nonlin, y_prev, u, u_prev);
        std::cout << "y" << i+1 << " = " << y_new << "\n";
        y_prev = y_nonlin;
        y_nonlin = y_new;
    }

    return 0;
}
