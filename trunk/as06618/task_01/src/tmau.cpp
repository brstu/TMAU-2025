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

double linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, const Coeffs& coeffs) {
    return coeffs.a * y_t - coeffs.b * y_prev * y_prev + coeffs.c * u_t + coeffs.d * sin(u_prev);
}

// Model coefficients
const double FEEDBACK_COEFF = 0.8;      // Feedback coefficient (a)
const double PREV_OUTPUT_COEFF = 0.2;   // Previous output squared coefficient (b)
const double INPUT_COEFF = 0.1;         // Input coefficient (c)
const double NONLINEAR_COEFF = 0.05;    // Nonlinear (sin) coefficient (d)

int main() {
    Coeffs coeffs = {FEEDBACK_COEFF, PREV_OUTPUT_COEFF, INPUT_COEFF, NONLINEAR_COEFF};
    int N = 20; 
    vector<double> y(N + 1, 0.0); 
    vector<double> u(N + 1, 0.0); 

    for (int t = 0; t <= N; t++) {
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
        double y_prev = (t == 0) ? 0.0 : y[t - 1];
        double u_prev = (t == 0) ? 0.0 : u[t - 1];
        y[t + 1] = nonlinear_model(y[t], y_prev, u[t], u_prev, coeffs);
        cout << "t=" << t + 1 << "  y=" << fixed << setprecision(4) << y[t + 1] << endl;
    }

    return 0;
}