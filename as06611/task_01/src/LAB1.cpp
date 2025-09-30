#include <iostream>
#include <vector>
#include <cmath>

/**
 * Temperature Model class for simulating linear and nonlinear temperature dynamics
 * Implements both linear and nonlinear difference equation models
 */
class TemperatureModel {
private:
    // System parameters as static constants (shared across all instances)
    constexpr static double FEEDBACK_COEFF_A = 0.8;    // Thermal inertia coefficient (0 < a < 1)
    constexpr static double INPUT_GAIN_B = 0.5;        // Linear input gain for heat source
    constexpr static double NONLINEAR_INPUT_GAIN_C = 0.3; // Nonlinear model input gain
    constexpr static double NONLINEARITY_COEFF_D = 0.1;   // Sinusoidal disturbance coefficient

    // Model state variables (only what changes per instance)
    double y_prev;
    double y_curr;

public:
    /**
     * Constructor initializes model state
     */
    TemperatureModel() : y_prev(0.0), y_curr(0.0) {
    }

    /**
     * Linear temperature model: y(k+1) = a*y(k) + b*u(k)
     * Represents first-order linear difference equation
     * where k - discrete time step
     * @param u Heat input at current time step
     * @return Temperature at next time step
     */
    double linearModel(double u) {
        double y_next = FEEDBACK_COEFF_A * y_curr + INPUT_GAIN_B * u;
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    /**
     * Nonlinear temperature model with squared and sinusoidal terms
     * y(k+1) = a*y(k) - b*y(k-1)² + c*u(k) + d*sin(u(k-1))
     * Includes nonlinear effects and periodic disturbances
     * where k - discrete time step
     * @param u Heat input at current time step
     * @param u_prev Heat input at previous time step
     * @return Temperature at next time step
     */
    double nonlinearModel(double u, double u_prev) {
        double y_next = FEEDBACK_COEFF_A * y_curr
            - INPUT_GAIN_B * std::pow(y_prev, 2)
            + NONLINEAR_INPUT_GAIN_C * u
            + NONLINEARITY_COEFF_D * std::sin(u_prev);
        y_prev = y_curr;
        y_curr = y_next;
        return y_next;
    }

    /**
     * Reset model state to initial conditions
     */
    void reset() {
        y_prev = 0.0;
        y_curr = 0.0;
    }

    /**
     * Get model parameters (for debugging or display)
     */
    static void printParameters() {
        std::cout << "Model Parameters:" << std::endl;
        std::cout << "Feedback coefficient (a): " << FEEDBACK_COEFF_A << std::endl;
        std::cout << "Linear input gain (b): " << INPUT_GAIN_B << std::endl;
        std::cout << "Nonlinear input gain (c): " << NONLINEAR_INPUT_GAIN_C << std::endl;
        std::cout << "Nonlinearity coefficient (d): " << NONLINEARITY_COEFF_D << std::endl;
    }
};

/**
 * Main function demonstrating temperature model simulation
 * Shows both linear and nonlinear model behavior with sample input data
 */
int main() {
    TemperatureModel model;

    // Display model parameters
    TemperatureModel::printParameters();
    std::cout << std::endl;

    // Heat input sequence simulating control signal variations
    const std::vector<double> heat_input = { 1.0, 1.2, 0.8, 1.5, 1.0, 0.7, 1.3, 0.9, 1.1, 0.6 };

    // Linear model simulation
    std::cout << "Linear temperature model simulation:" << std::endl;
    std::cout << "Time k\tHeat Input u(k)\tTemperature y(k)" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    model.reset();

    for (size_t k = 0; k < heat_input.size(); ++k) {
        double temperature = model.linearModel(heat_input[k]);
        std::cout << k + 1 << "\t" << heat_input[k] << "\t\t" << temperature << std::endl;
    }

    // Nonlinear model simulation  
    std::cout << "\nNonlinear temperature model simulation:" << std::endl;
    std::cout << "Time k\tHeat Input u(k)\tTemperature y(k)" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    model.reset();

    for (size_t k = 0; k < heat_input.size(); ++k) {
        double previous_heat_input = (k == 0) ? 0.0 : heat_input[k - 1];
        double temperature = model.nonlinearModel(heat_input[k], previous_heat_input);
        std::cout << k + 1 << "\t" << heat_input[k] << "\t\t" << temperature << std::endl;
    }

    return 0;
}