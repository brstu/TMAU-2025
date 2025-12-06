#include <iostream>
#include <vector>
#include <cmath>

class TemperatureModel {
private:
    double a;
    double b;
    double c;
    double d;
    double y_prev = 0;
    double y_prev2 = 0;
    double u_prev = 0;
    bool is_nonlinear;

public:
    // Linear model constructor
    TemperatureModel(double a_val, double b_val)
        : a(a_val), b(b_val), c(0), d(0), is_nonlinear(false) {
    }

    // Nonlinear model constructor
    TemperatureModel(double a_val, double b_val, double c_val, double d_val)
        : a(a_val), b(b_val), c(c_val), d(d_val), is_nonlinear(true) {
    }

    void setInitialConditions(double y0, double y1 = 0, double u0 = 0) {
        y_prev = y0;
        y_prev2 = y1;
        u_prev = u0;
    }

    double calculateNext(double u_current) {
        double y_next;

        if (is_nonlinear) {
            // Nonlinear model: y_{τ+1} = a*y_τ - b*y_{τ-1}^2 + c*u_τ + d*sin(u_{τ-1})
            y_next = a * y_prev - b * y_prev2 * y_prev2 + c * u_current + d * sin(u_prev);
        }
        else {
            // Linear model: y_{τ+1} = a*y_τ + b*u_τ
            y_next = a * y_prev + b * u_current;
        }

        // Update previous values
        y_prev2 = y_prev;
        y_prev = y_next;
        u_prev = u_current;

        return y_next;
    }

    double getCurrentTemperature() const {
        return y_prev;
    }
};

void testLinearModel() {
    std::cout << "=== LINEAR MODEL TEST ===" << std::endl;

    double a = 0.8;
    double b = 0.2;

    TemperatureModel model(a, b);
    model.setInitialConditions(20.0);

    std::vector<double> control_inputs = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };

    std::cout << "Time\tControl\tTemperature" << std::endl;
    std::cout << "0\t-\t20.0" << std::endl;

    for (size_t t = 0; t < control_inputs.size(); ++t) {
        double u = control_inputs[t];
        double y = model.calculateNext(u);
        std::cout << t + 1 << "\t" << u << "\t" << y << std::endl;
    }
}

void testNonlinearModel() {
    std::cout << "\n=== NONLINEAR MODEL TEST ===" << std::endl;

    double a = 0.7;
    double b = 0.01;
    double c = 0.3;
    double d = 0.1;

    TemperatureModel model(a, b, c, d);
    model.setInitialConditions(20.0, 19.5, 5.0);

    std::vector<double> control_inputs = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };

    std::cout << "Time\tControl\tTemperature" << std::endl;
    std::cout << "0\t5.0\t20.0" << std::endl;

    for (size_t t = 0; t < control_inputs.size(); ++t) {
        double u = control_inputs[t];
        double y = model.calculateNext(u);
        std::cout << t + 1 << "\t" << u << "\t" << y << std::endl;
    }
}

int main() {
    testLinearModel();
    testNonlinearModel();
    return 0;
}