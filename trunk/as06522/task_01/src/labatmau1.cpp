#include <iostream>
#include <cmath>
#include <array>
using std::cout;
using std::endl;

const int TIME_STEPS = 10;
const double COEFFICIENT_A = 0.99;
const double COEFFICIENT_B = 0.01;
const double COEFFICIENT_C = 0.5;
const double COEFFICIENT_D = 0.1;
const double INITIAL_VALUE = 18;

// Линейная модель
double linearModel(double currentValue, double controlInput) {
    return COEFFICIENT_A * currentValue + COEFFICIENT_B * controlInput;
}

// Нелинейная модель
double nonlinearModel(double currentValue, double previousValue, double controlInput, double previousControlInput) {
    return COEFFICIENT_A * currentValue - COEFFICIENT_B * pow(previousValue, 2) + COEFFICIENT_C * controlInput + COEFFICIENT_D * sin(previousControlInput);
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Линейная модель" << endl;
    cout << "y0 = " << INITIAL_VALUE << endl;
    std::array<double, TIME_STEPS> controlInputs = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
    double currentValue = INITIAL_VALUE;
    for (int step = 0; step < TIME_STEPS; step++) {
        currentValue = linearModel(currentValue, controlInputs[step]);
        cout << "y" << step + 1 << " = " << currentValue << endl;
    }
    cout << "\n";

    double previousValue = INITIAL_VALUE;
    currentValue = INITIAL_VALUE;
    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << INITIAL_VALUE << endl;
    for (int step = 0; step < TIME_STEPS; step++) {
        double currentControlInput = controlInputs[step];
        double previousControlInput = (step == 0) ? controlInputs[0] : controlInputs[step - 1];
        double newValue = nonlinearModel(currentValue, previousValue, currentControlInput, previousControlInput);
        cout << "y" << step + 1 << " = " << newValue << endl;
        previousValue = currentValue;
        currentValue = newValue;
    }
    return 0;
}
