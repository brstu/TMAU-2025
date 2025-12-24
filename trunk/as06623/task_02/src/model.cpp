#include "model.h"
#include <cmath>

std::vector<double> simulateLinear(double controlInput) {
    std::vector<double> output(iterationsCount);
    output[0] = initialTemperature;

    for (int i = 0; i < iterationsCount - 1; ++i) {
        output[i + 1] = coeffA * output[i] + coeffB * controlInput;
    }

    return output;
}

std::vector<double> simulateNonlinear(double controlInput) {
    std::vector<double> output(iterationsCount);
    output[0] = initialTemperature;
    output[1] = coeffA * output[0] - coeffB * output[0] * output[0] + coeffC * controlInput + coeffD * sin(controlInput);

    for (int i = 2; i < iterationsCount; ++i) {
        output[i] = coeffA * output[i - 1] - coeffB * output[i - 1] * output[i - 1] + coeffC * controlInput + coeffD * sin(controlInput);
    }

    return output;
}
