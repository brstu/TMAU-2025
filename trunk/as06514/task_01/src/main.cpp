#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class TemperatureModel {
private:
    double a, b, c, d;
    double y_prev;
    double y_prev2;
    double u_prev;
    
public:
    TemperatureModel(double a_val, double b_val, double c_val = 0, double d_val = 0) 
        : a(a_val), b(b_val), c(c_val), d(d_val), y_prev(0), y_prev2(0), u_prev(0) {}
    
    double linearModel(double u_current) {
        double y_next = a * y_prev + b * u_current;
        y_prev = y_next;
        return y_next;
    }
    
    double nonlinearModel(double u_current) {
        double y_next = a * y_prev - b * y_prev2 * y_prev2 + c * u_current + d * sin(u_prev);
        
        y_prev2 = y_prev;
        y_prev = y_next;
        u_prev = u_current;
        
        return y_next;
    }
    
    void reset(double initial_temp = 0) {
        y_prev = initial_temp;
        y_prev2 = initial_temp;
        u_prev = 0;
    }
    
    void setInitialTemperature(double temp) {
        y_prev = temp;
        y_prev2 = temp;
    }
};

void testModel() {
    const double a_linear = 0.8;
    const double b_linear = 0.2;
    
    const double a_nonlinear = 0.7;
    const double b_nonlinear = 0.1;
    const double c_nonlinear = 0.3;
    const double d_nonlinear = 0.05;
    
    TemperatureModel linearModel(a_linear, b_linear);
    TemperatureModel nonlinearModel(a_nonlinear, b_nonlinear, c_nonlinear, d_nonlinear);
    
    const double initial_temp = 20.0;
    linearModel.setInitialTemperature(initial_temp);
    nonlinearModel.setInitialTemperature(initial_temp);
    
    const int time_steps = 50;
    
    std::vector<double> u_input(time_steps);
    
    for (int t = 0; t < time_steps; ++t) {
        if (t < 10) {
            u_input[t] = 0;
        } else if (t < 30) {
            u_input[t] = 5.0;
        } else {
            u_input[t] = 2.0;
        }
    }
    
    std::vector<double> y_linear(time_steps);
    std::vector<double> y_nonlinear(time_steps);
    
    for (int t = 0; t < time_steps; ++t) {
        y_linear[t] = linearModel.linearModel(u_input[t]);
        y_nonlinear[t] = nonlinearModel.nonlinearModel(u_input[t]);
    }
    
    std::cout << "Time Simulation Results:\n";
    std::cout << "Time\tInput\tLinear\tNonlinear\n";
    std::cout << "----\t-----\t------\t---------\n";
    
    for (int t = 0; t < time_steps; ++t) {
        if (t % 5 == 0) {
            std::cout << std::setw(2) << t << "\t"
                      << std::fixed << std::setprecision(2)
                      << u_input[t] << "\t"
                      << y_linear[t] << "\t"
                      << y_nonlinear[t] << "\n";
        }
    }
}

void stepResponseDemo() {
    std::cout << "\n=== Step Response Demonstration ===\n";
    
    TemperatureModel model(0.9, 0.1);
    
    const int steps = 20;
    std::cout << "Step response (u = 1.0 for all t):\n";
    std::cout << "Time\tTemperature\n";
    
    for (int t = 0; t < steps; ++t) {
        double temp = model.linearModel(1.0);
        std::cout << t << "\t" << std::fixed << std::setprecision(3) << temp << "\n";
    }
}

int main() {
    std::cout << "Temperature Control Object Simulation\n";
    std::cout << "=====================================\n\n";
    
    testModel();
    
    stepResponseDemo();
    
    std::cout << "\n=== Individual Model Usage Example ===\n";
    
    TemperatureModel linear(0.85, 0.15);
    linear.setInitialTemperature(25.0);
    
    std::cout << "Linear model simulation:\n";
    for (int i = 0; i < 5; ++i) {
        double temp = linear.linearModel(2.0);
        std::cout << "Step " << i << ": Temperature = " << temp << "°C\n";
    }
    
    TemperatureModel nonlinear(0.75, 0.05, 0.25, 0.1);
    nonlinear.setInitialTemperature(25.0);
    
    std::cout << "\nNonlinear model simulation:\n";
    for (int i = 0; i < 5; ++i) {
        double temp = nonlinear.nonlinearModel(2.0);
        std::cout << "Step " << i << ": Temperature = " << temp << "°C\n";
    }
    
    return 0;
}