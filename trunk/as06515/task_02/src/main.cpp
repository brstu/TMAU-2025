#include <iostream>
#include <vector>
#include "temperature_model.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    vector<double> inputs = {3, 4, 5, 6, 7, 8, 9, 10, 9, 8};

    TemperatureModel model(0.7, 0.3, 0.05, 0.01, 20.0, inputs);

    model.runLinear();
    model.runNonlinear();

    return 0;
}