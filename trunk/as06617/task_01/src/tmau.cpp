#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Coeffs {
    double a;
    double b;
    double c;
    double d;
};

// Computes the next output of a linear model.
// Parameters:
//   y_t: Output (e.g., temperature) at time t
//   u_t: Input at time t
//   a: Coefficient for the previous output
//   b: Coefficient for the input
// Returns:
//   The output at time t+1
double linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

// Computes the next output of a nonlinear model.
// Parameters:
//   y_t: Output at time t
//   y_prev: Output at time t-1
//   u_t: Input at time t
//   u_prev: Input at time t-1
//   coeffs: Struct containing coefficients a, b, c, d
// Returns:
//   The output at time t+1, including nonlinear effects
double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, const Coeffs& coeffs) {
    return coeffs.a * y_t - coeffs.b * y_prev * y_prev + coeffs.c * u_t + coeffs.d * sin(u_prev);
}

int main() {
    Coeffs coeffs = {0.8, 0.2, 0.1, 0.05};
    const int SIMULATION_STEPS = 20;
    int N = SIMULATION_STEPS;
    vector<double> y(N + 1, 0.0); 
    vector<double> u(N + 1, 0.0); 

    for (int t = 0; t < N + 1; t++) {
        u[t] = (t < 5) ? 0.0 : 1.0;
    }

    cout << "Linear model" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], coeffs.a, coeffs.b);
        cout << "t=" << t + 1 << "  y=" << fixed << setprecision(4) << y[t + 1] << endl;
    }

    fill(y.begin(), y.end(), 0.0);

    cout << "\nNonlinear model" << endl;
    for (int t = 0; t < N; t++) {
        if (t == 0) {
            y[t + 1] = nonlinear_model(y[t], 0.0, u[t], 0.0, coeffs);
        } else {
            y[t + 1] = nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], coeffs);
        }
        cout << "t=" << t + 1 << "  y=" << fixed << setprecision(4) << y[t + 1] << endl;
    }

    return 0;
}
