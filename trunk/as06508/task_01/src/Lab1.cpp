#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct ModelParams {
    double a = 0.8, b = 0.001, c = 0.5, d = 0.02;
    int time_steps = 10;
    double initial_temp = 25.0;
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
        y[1] = y[0] * 0.95;
        for (int t = 1; t < params.time_steps; ++t) {
            y[t + 1] = params.a * y[t] - params.b * pow(y[t - 1], 2) + params.c * u[t] + params.d * sin(u[t - 1]);
        }
        cout << "Nonlinear Model Results:\n";
    }

    cout << "Time\tTemperature\n----------------\n";
    for (int t = 0; t <= params.time_steps; ++t) {
        cout << t << "\t" << y[t] << endl;  // Simple output without formatting
    }
    cout << endl;
}

int main() {
    ModelParams params;
    vector<double> u(params.time_steps);

    for (int t = 0; t < params.time_steps; ++t) {
        u[t] = 10.0 + 2.0 * sin(t * 0.5);
    }

    simulateAndPrint(params, u, true);
    simulateAndPrint(params, u, false);

    return 0;
}