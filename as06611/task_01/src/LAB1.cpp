#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>

using namespace std;

struct ModelParams {
    double a;
    double b;
    double c;
    double d;
};

// --- Linear model: y(t+1) = a*y(t) + b*u(t)
vector<double> simulateLinear(int steps, double y0, const ModelParams& params, const vector<double>& u) {
    if (steps <= 0 || u.empty()) {
        throw invalid_argument("Steps must be positive and input vector u must not be empty.");
    }

    vector<double> y(steps + 1, 0.0);
    y[0] = y0;

    for (int t = 0; t < steps; t++) {
        y[t + 1] = params.a * y[t] + params.b * u[t];
    }
    return y;
}

// --- Nonlinear model: y(t+1) = a*y(t) - b*y(t-1)^2 + c*u(t) + d*sin(u(t-1))
vector<double> simulateNonlinear(int steps, double y0, const ModelParams& params, const vector<double>& u) {
    if (steps <= 0 || u.empty()) {
        throw invalid_argument("Steps must be positive and input vector u must not be empty.");
    }

    vector<double> y(steps + 1, 0.0);
    y[0] = y0;

    for (int t = 0; t < steps; t++) {
        double prevY = (t > 0) ? y[t - 1] : 0.0;
        double prevU = (t > 0) ? u[t - 1] : 0.0;

        y[t + 1] = params.a * y[t]
            - params.b * prevY * prevY
            + params.c * u[t]
            + params.d * sin(prevU);
    }
    return y;
}

// --- Output results
void printResults(const vector<double>& u, const vector<double>& yLinear, const vector<double>& yNonlinear) {
    cout << "Step\tu(t)\ty_linear(t)\ty_nonlinear(t)" << endl;

    int steps = static_cast<int>(yLinear.size()) - 1;
    for (int t = 0; t <= steps; t++) {
        cout << t << "\t";
        if (t < static_cast<int>(u.size())) {
            cout << u[t] << "\t";
        }
        else {
            cout << "-\t";
        }
        cout << yLinear[t] << "\t\t" << yNonlinear[t] << endl;
    }
}

int main() {
    try {
        // Simulation constants
        const int steps = 20;
        const double y0 = 20.0;

        // Parameters for models
        const ModelParams params{ 0.8, 0.5, 0.3, 0.2 };

        // Input signal u(t)
        vector<double> u(steps, 0.0);
        for (int t = 0; t < steps; t++) {
            u[t] = 5.0 + 2.0 * sin(0.3 * static_cast<double>(t));
        }

        // Run simulations
        vector<double> yLinear = simulateLinear(steps, y0, params, u);
        vector<double> yNonlinear = simulateNonlinear(steps, y0, params, u);

        // Print results
        printResults(u, yLinear, yNonlinear);

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
