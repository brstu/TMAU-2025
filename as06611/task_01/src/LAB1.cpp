#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class TemperatureModel {
private:
    double a, b, c, d;
    double y_prev, y_curr;

public:
    // Constructor with parameters initialization
    TemperatureModel(double a_val, double b_val, double c_val, double d_val)
        : a(a_val), b(b_val), c(c_val), d(d_val), y_prev(0), y_curr(0) {
    }

    // Linear model: y(τ+1) = a*y(τ) + b*u(τ)
    double linearModel(double u) {
        double y_next = a * y_curr + b * u;
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    // Nonlinear model: y(τ+1) = a*y(τ) - b*y(τ-1)² + c*u(τ) + d*sin(u(τ-1))
    double nonlinearModel(double u, double u_prev) {
        double y_next = a * y_curr - b * pow(y_prev, 2) + c * u + d * sin(u_prev);
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    // Reset model state to initial conditions
    void reset() {
        y_prev = 0;
        y_curr = 0;
    }
};

int main() {
    // MODEL PARAMETERS INITIALIZATION
    double a = 0.8;  // coefficient for previous temperature value
    double b = 0.5;  // coefficient for input signal (linear model)
    double c = 0.3;  // coefficient for input signal (nonlinear model)
    double d = 0.1;  // coefficient for sinusoidal component

    // INPUT SIGNALS INITIALIZATION
    vector<double> u = { 1.0, 1.2, 0.8, 1.5, 1.0, 0.7, 1.3, 0.9, 1.1, 0.6 };

    // MODEL INITIALIZATION WITH PARAMETERS
    TemperatureModel model(a, b, c, d);

    // LINEAR MODEL SIMULATION
    cout << "Linear model:" << endl;
    model.reset();  // reset initial conditions
    for (size_t i = 0; i < u.size(); ++i) {
        double y = model.linearModel(u[i]);
        cout << "t=" << (i + 1) << ", u=" << u[i] << ", y=" << y << endl;
    }

    // NONLINEAR MODEL SIMULATION
    cout << "\nNonlinear model:" << endl;
    model.reset();  // reset initial conditions
    for (size_t i = 0; i < u.size(); ++i) {
        double u_prev = (i == 0) ? 0 : u[i - 1];  // previous input signal
        double y = model.nonlinearModel(u[i], u_prev);
        cout << "t=" << (i + 1) << ", u=" << u[i] << ", y=" << y << endl;
    }

    return 0;
}