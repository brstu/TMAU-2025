#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

struct Coeffs {
    double a, b, c, d;
};

double linear_model(double y_t, double u_t, double a, double b) {
    return a * y_t + b * u_t;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, const Coeffs& coeffs) {
    return coeffs.a * y_t - coeffs.b * y_prev * y_prev + coeffs.c * u_t + coeffs.d * sin(u_prev);
}

void simulate_and_print(const string& model_name, bool is_linear, const Coeffs& coeffs, int N) {
    vector<double> y(N + 1, 0.0);
    vector<double> u(N + 1, 1.0); // Ступенчатое воздействие
    
    cout << model_name << endl;
    
    if (is_linear) {
        for (int t = 0; t < N; t++) {
            y[t + 1] = linear_model(y[t], u[t], coeffs.a, coeffs.b);
            cout << "t=" << t + 1 << "  y=" << fixed << setprecision(4) << y[t + 1] << endl;
        }
    } else {
        for (int t = 1; t < N; t++) {
            y[t + 1] = nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], coeffs);
            cout << "t=" << t + 1 << "  y=" << fixed << setprecision(4) << y[t + 1] << endl;
        }
    }
    cout << endl;
}

int main() {
    Coeffs coeffs = {0.8, 0.2, 0.1, 0.05};
    int N = 20;

    simulate_and_print("Linear model:", true, coeffs, N);
    simulate_and_print("Nonlinear model:", false, coeffs, N);

    return 0;
}