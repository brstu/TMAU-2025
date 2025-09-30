#include <iostream>
#include <vector>
#include <cmath>

class TemperatureModel {
private:
    double a, b, c, d;
    double y_prev, y_curr;

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val)
        : a(a_val), b(b_val), c(c_val), d(d_val), y_prev(0), y_curr(0) {
    }

    double linearModel(double u) {
        double y_next = a * y_curr + b * u;
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    double nonlinearModel(double u, double u_prev) {
        double y_next = a * y_curr - b * std::pow(y_prev, 2) + c * u + d * std::sin(u_prev);
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    void reset() {
        y_prev = 0;
        y_curr = 0;
    }
};

int main() {
    double a = 0.8;
    double b = 0.5;
    double c = 0.3;
    double d = 0.1;

    std::vector<double> u = { 1.0, 1.2, 0.8, 1.5, 1.0, 0.7, 1.3, 0.9, 1.1, 0.6 };

    TemperatureModel model(a, b, c, d);

    std::cout << "Linear model:" << std::endl;
    model.reset();
    for (size_t i = 0; i < u.size(); ++i) {
        double y = model.linearModel(u[i]);
        std::cout << "t=" << (i + 1) << ", u=" << u[i] << ", y=" << y << std::endl;
    }

    std::cout << "\nNonlinear model:" << std::endl;
    model.reset();
    for (size_t i = 0; i < u.size(); ++i) {
        double u_prev = (i == 0) ? 0 : u[i - 1];
        double y = model.nonlinearModel(u[i], u_prev);
        std::cout << "t=" << (i + 1) << ", u=" << u[i] << ", y=" << y << std::endl;
    }

    return 0;
}