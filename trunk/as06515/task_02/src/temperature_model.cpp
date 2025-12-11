#include "temperature_model.h"
#include <iostream>
#include <cmath>

using namespace std;

TemperatureModel::TemperatureModel(double a_val, double b_val, double c_val, double d_val,
                    double temp, const std::vector<double>& inputs, bool verbose_mode)
    : a(a_val), b(b_val), c(c_val), d(d_val), startTemp(temp), 
      heatInput(inputs), verbose(verbose_mode) {
    linearResults.clear();
    nonlinearResults.clear();
}

void TemperatureModel::runLinear() {
    linearResults.clear();
    if (verbose) {
        cout << "Linear model results:" << endl;
    }
    double current = startTemp;

    for (size_t i = 0; i < heatInput.size(); i++) {
        current = a * current + b * heatInput[i];
        linearResults.push_back(current);
        if (verbose) {
            cout << "Y" << i + 1 << ": " << current << endl;
        }
    }
}

void TemperatureModel::runNonlinear() {
    nonlinearResults.clear();
    if (verbose) {
        cout << "\nResults of the nonlinear model:" << endl;
    }
    double prev = startTemp;
    double current = startTemp;

    for (size_t i = 0; i < heatInput.size(); i++) {
        double prevHeat = (i > 0) ? heatInput[i - 1] : 0;
        double next = a * current - b * prev + c * heatInput[i] + d * sin(prevHeat);
        nonlinearResults.push_back(next);
        if (verbose) {
            cout << "Y" << i + 1 << ": " << next << endl;
        }
        prev = current;
        current = next;
    }
}