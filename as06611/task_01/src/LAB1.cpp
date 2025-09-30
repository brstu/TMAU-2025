#include <iostream>
#include <vector>
#include <cmath>

class TemperatureModel {
private:
    double a, b, c, d;
    double y_prev, y_curr;

public:
    // System parameters for the temperature model:
    // FEEDBACK_COEFF_A: Feedback coefficient for previous temperature (thermal inertia)
    constexpr static double FEEDBACK_COEFF_A = 0.8;
    // INPUT_GAIN_B: Linear gain applied to the heat input signal
    constexpr static double INPUT_GAIN_B = 0.5;
    // NONLINEAR_INPUT_GAIN_C: Gain for current heat input in nonlinear model
    constexpr static double NONLINEAR_INPUT_GAIN_C = 0.3;
    // NONLINEARITY_COEFF_D: Coefficient for sinusoidal nonlinearity (periodic disturbances)
    constexpr static double NONLINEARITY_COEFF_D = 0.1;

    TemperatureModel()
        : a(FEEDBACK_COEFF_A), b(INPUT_GAIN_B), c(NONLINEAR_INPUT_GAIN_C),
        d(NONLINEARITY_COEFF_D), y_prev(0), y_curr(0) {
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
    TemperatureModel model;

    // Heat input sequence (simulated control signal)
    std::vector<double> heat_input = { 1.0, 1.2, 0.8, 1.5, 1.0, 0.7, 1.3, 0.9, 1.1, 0.6 };

    // Linear model simulation
    std::cout << "Linear temperature model:" << std::endl;
    model.reset();
    for (size_t i = 0; i < heat_input.size(); ++i) {
        double temperature = model.linearModel(heat_input[i]);
        std::cout << "Time=" << (i + 1)
            << ", Heat input=" << heat_input[i]
            << ", Temperature=" << temperature << std::endl;
    }

    // Nonlinear model simulation
    std::cout << "\nNonlinear temperature model:" << std::endl;
    model.reset();
    for (size_t i = 0; i < heat_input.size(); ++i) {
        double prev_heat_input = (i == 0) ? 0 : heat_input[i - 1];
        double temperature = model.nonlinearModel(heat_input[i], prev_heat_input);
        std::cout << "Time=" << (i + 1)
            << ", Heat input=" << heat_input[i]
            << ", Temperature=" << temperature << std::endl;
    }

    return 0;
}