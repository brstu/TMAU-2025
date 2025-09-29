#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct LinearModel {
    double a, b;
    double step(double y, double u) const {
        return a * y + b * u;
    }
};

struct NonlinearModel {
    double a, b, c, d;
    double step(double y, double u, double prev_u) const {
        return a * y - b * y * y + c * u + d * sin(prev_u);
    }
};

int main() {
    int n;
    double y0;
    double u_val;

    double a = 0.9;
    double b = 0.2;
    double c = 0.15;
    double d = 0.05;

    cout << "Enter number of steps n: ";
    cin >> n;
    cout << "Enter initial temperature y0: ";
    cin >> y0;
    cout << "Enter constant heating u: ";
    cin >> u_val;

    LinearModel linear{a, b};
    NonlinearModel nonlinear{a, 0.01, c, d};

    vector<double> y_lin(n + 1, 0.0);
    vector<double> y_nonlin(n + 1, 0.0);
    vector<double> u(n + 1, u_val);

    y_lin[0] = y0;
    y_nonlin[0] = y0;

    for (int t = 0; t < n; ++t) {
        y_lin[t + 1] = linear.step(y_lin[t], u[t]);
        double prev_u = (t > 0) ? u[t - 1] : 0.0;
        y_nonlin[t + 1] = nonlinear.step(y_nonlin[t], u[t], prev_u);
    }

    cout << "\nSimulation results:\n";
    cout << "Step\tLinear\t\tNonlinear\n";
    cout << "---------------------------------\n";
    for (int t = 0; t <= n; ++t) {
        cout << t << "\t" 
             << fixed << setprecision(4) << y_lin[t] << "\t\t"
             << y_nonlin[t] << "\n";
    }

    return 0;
}
