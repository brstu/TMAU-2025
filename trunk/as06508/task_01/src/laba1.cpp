#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct ModelParams {
    const double INPUT_OFFSET = 10.0;
    const double INPUT_AMPLITUDE = 2.0;
    const double INPUT_FREQUENCY = 0.5;
    const double INPUT_E = 0.95;
    const double a = 0.85;
    const double b = 0.002;
    const double c = 0.6;
    const double d = 0.025;
    int time_steps = 10;
    double initial_temp = 24.0;
};

void simulateAndPrint(const ModelParams& params, const vector<double>& u, bool isLinear) {
    vector<double> y(params.time_steps + 1);
    y[0] = params.initial_temp;

    if (isLinear) {
        for (int t = 0; t < params.time_steps; ++t) {
            y[t + 1] = params.a * y[t] + params.b * u[t];
        }
        cout << "Linear Model Results:\n";
    }
    else {
        y[1] = y[0] * params.INPUT_E;
        for (int t = 1; t < params.time_steps; ++t) {
            y[t + 1] = params.a * y[t] - params.b * pow(y[t - 1], 2) + params.c * u[t] + params.d * sin(u[t - 1]);
        }
        cout << "Nonlinear Model Results:\n";
    }

    cout << "Time\tTemperature\n----------------\n";
    for (int t = 0; t <= params.time_steps; ++t) {
        cout << t << "\t" << y[t] << endl;
    }
    cout << endl;
}

int main() {
    ModelParams params;
    vector<double> u(params.time_steps);

    for (int t = 0; t < params.time_steps; ++t) {
        u[t] = params.INPUT_OFFSET + params.INPUT_AMPLITUDE * sin(t * params.INPUT_FREQUENCY);
    }

    simulateAndPrint(params, u, true);
    simulateAndPrint(params, u, false);

    return 0;
}
