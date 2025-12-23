#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>

class ITemperatureModel {
public:
    virtual void setInitialConditions(double y0, double y1 = 0, double u0 = 0) = 0;
    virtual double calculateNext(double u_current) = 0;
    virtual double getCurrentTemperature() const = 0;
    virtual ~ITemperatureModel() = default;
};

class TemperatureModel : public ITemperatureModel {
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
    TemperatureModel(double a_val, double b_val, double c_val = 0, double d_val = 0)
        : a(a_val), b(b_val), c(c_val), d(d_val), is_nonlinear(c_val != 0 || d_val != 0) {
    }

    void setInitialConditions(double y0, double y1 = 0, double u0 = 0) override {
        y_prev = y0;
        y_prev2 = y1;
        u_prev = u0;
    }

    double calculateNext(double u_current) override {
        double y_next = is_nonlinear ?
            a * y_prev - b * y_prev2 * y_prev2 + c * u_current + d * sin(u_prev) :
            a * y_prev + b * u_current;

        y_prev2 = y_prev;
        y_prev = y_next;
        u_prev = u_current;

        return y_next;
    }

    double getCurrentTemperature() const override {
        return y_prev;
    }
};

void runSimulation(ITemperatureModel& model, const std::vector<double>& control_inputs, std::size_t steps, double timestep) {
    std::cout << std::setw(4) << "Time" << std::setw(8) << "Control" << std::setw(12) << "Temperature" << std::endl;

    for (std::size_t t = 0; t < steps; ++t) {
        double u = (t < control_inputs.size()) ? control_inputs[t] : 0;
        double y = model.calculateNext(u);
        std::cout << std::fixed << std::setprecision(1) << std::setw(4) << t << std::setw(8) << u << std::setw(12) << y << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(int(timestep * 1000)));
    }
}

int main() {
    double a_linear = 0.8;
    double b_linear = 0.2;
    double a_nonlinear = 0.7;
    double b_nonlinear = 0.01;
    double c = 0.3;
    double d = 0.1;

    // Линейная модель
    TemperatureModel linear_model(a_linear, b_linear);
    linear_model.setInitialConditions(20.0);

    std::vector<double> control_inputs_linear = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };
    runSimulation(linear_model, control_inputs_linear, control_inputs_linear.size(), 1.0);

    std::cout << "\n=== NONLINEAR MODEL TEST ===" << std::endl;

    // Нелинейная модель
    TemperatureModel nonlinear_model(a_nonlinear, b_nonlinear, c, d);
    nonlinear_model.setInitialConditions(20.0, 19.5, 5.0);

    std::vector<double> control_inputs_nonlinear = { 10, 15, 20, 25, 30, 25, 20, 15, 10, 5 };
    runSimulation(nonlinear_model, control_inputs_nonlinear, control_inputs_nonlinear.size(), 1.0);

    return 0;
}