#include <iostream>
#include <vector>
#include <cmath>

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

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, Coeffs coeffs) {
    return coeffs.a * y_t - coeffs.b * y_prev * y_prev + coeffs.c * u_t + coeffs.d * sin(u_prev);
}

int main() {
    Coeffs coeffs = {0.8, 0.2, 0.1, 0.05};

    int N = 20; 

    vector<double> y(N + 1, 0.0); 
    vector<double> u(N + 1, 0.0); 

    for (int t = 0; t <= N; t++) {
        u[t] = (t < 5) ? 0.0 : 1.0;
    }

    cout << "Linear model" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], coeffs.a, coeffs.b);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    fill(y.begin(), y.end(), 0.0);

    cout << "\nNonlinear model" << endl;
    for (int t = 1; t < N; t++) {
        y[t + 1] = nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], coeffs);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    return 0;
}
