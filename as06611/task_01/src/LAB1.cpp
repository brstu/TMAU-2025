#include <iostream>
#include <vector>
#include <cmath>


class TemperatureModel {
private:
    // System parameters with descriptive names and comments
    constexpr static double FEEDBACK_COEFF_A = 0.8;    // Thermal inertia coefficient (0 < a < 1)
    constexpr static double INPUT_GAIN_B = 0.5;        // Linear input gain for heat source
    constexpr static double NONLINEAR_INPUT_GAIN_C = 0.3; // Nonlinear model input gain
    constexpr static double NONLINEARITY_COEFF_D = 0.1;   // Sinusoidal disturbance coefficient

    // Model state variables
    double a;
    double b;
    double c;
    double d;
    double y_prev;
    double y_curr;

public:
    TemperatureModel()
        : a(FEEDBACK_COEFF_A), b(INPUT_GAIN_B), c(NONLINEAR_INPUT_GAIN_C),
        d(NONLINEARITY_COEFF_D), y_prev(0.0), y_curr(0.0) {
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
        y_prev = 0.0;
        y_curr = 0.0;
    }
};


int main() {
    TemperatureModel model;

    // Heat input sequence simulating control signal variations
    const std::vector<double> heat_input = { 1.0, 1.2, 0.8, 1.5, 1.0, 0.7, 1.3, 0.9, 1.1, 0.6 };

    // Linear model simulation
    std::cout << "Linear temperature model simulation:" << std::endl;
    std::cout << "Time\tHeat Input\tTemperature" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    model.reset();

    for (size_t i = 0; i < heat_input.size(); ++i) {
        double temperature = model.linearModel(heat_input[i]);
        std::cout << i + 1 << "\t" << heat_input[i] << "\t\t" << temperature << std::endl;
    }

    // Nonlinear model simulation  
    std::cout << "\nNonlinear temperature model simulation:" << std::endl;
    std::cout << "Time\tHeat Input\tTemperature" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    model.reset();

    for (size_t i = 0; i < heat_input.size(); ++i) {
        double previous_heat_input = (i == 0) ? 0.0 : heat_input[i - 1];
        double temperature = model.nonlinearModel(heat_input[i], previous_heat_input);
        std::cout << i + 1 << "\t" << heat_input[i] << "\t\t" << temperature << std::endl;
    }

    return 0;
}