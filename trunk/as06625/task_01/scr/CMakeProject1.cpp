#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct LinearModel {
    double a, b;

    double compute(double y, double u) const {
        return a * y + b * u;
    }
};

struct NonlinearModel {
    double a, b, c, d;

    double compute(double y, double u, double prev_u) const {
        return a * y - b * y * y + c * u + d * sin(prev_u);
    }
};

void simulate(int n, double y0, double u_val, const LinearModel& linear, const NonlinearModel& nonlinear) {
    vector<double> y_lin(n + 1);
    vector<double> y_nonlin(n + 1);
    vector<double> u(n + 1, u_val);

    // Set initial value
    y_lin[0] = y0;
    y_nonlin[0] = y0;

    // Simulation
    for (int t = 0; t < n; ++t) {
        y_lin[t + 1] = linear.compute(y_lin[t], u[t]);
        double prev_u = (t > 0) ? u[t - 1] : 0.0;
        y_nonlin[t + 1] = nonlinear.compute(y_nonlin[t], u[t], prev_u);
    }

    // Output simulation results
    cout << "\nSimulation results:\n";
    cout << "Step\tLinear\t\tNonlinear\n";
    cout << "---------------------------------\n";

    for (int t = 0; t <= n; ++t) {
        cout << t << "\t"
            << fixed << setprecision(4) << y_lin[t] << "\t\t"
            << fixed << setprecision(4) << y_nonlin[t] << "\n";
    }
}

int main() {
    int n;
    double y0;
    double u_val;

    // Model parameters with new values
    double a = 1.2;
    double b = 0.5;
    double c = 0.3;
    double d = 0.1;

    cout << "Enter the number of steps n: ";
    cin >> n;
    cout << "Enter the initial temperature y0: ";
    cin >> y0;
    cout << "Enter the constant heating u: ";
    cin >> u_val;

    LinearModel linear{ a, b };
    NonlinearModel nonlinear{ a, 0.01, c, d };

    // Start simulation
    simulate(n, y0, u_val, linear, nonlinear);

    return 0;
}
