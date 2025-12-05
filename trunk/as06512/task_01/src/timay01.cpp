#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

///constants
const int n = 10;
const double a = 0.98;
const double b = 0.02;
const double c = 0.4;
const double d = 0.15;
const double Y0 = 20.0;
const double u = 8.0;

///Linear mathematical model yₖ₊₁ = a * yₖ + b * u
double linear(double y, double u_val) {
    return a * y + b * u_val;
}

// Nonlinear mathematical model yₖ₊₁ = a * yₖ - b * yₖ₋₁² + c * uₖ + d * sin(uₖ₋₁)
double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * yt1 * yt1 + c * ut + d * sin(ut1);
}

/**
 * The program's main function displays the simulation results of both models and performs:
 * 1. Simulation of a linear system: yₖ₊₁ = a * yₖ + b * u
 * 2. Modeling of a nonlinear system: yₖ₊₁ = a * yₖ - b * yₖ₋₁² + c * uₖ + d * sin(uₖ₋₁)
 */
int main() {
    double y;

    cout << "Линейная модель:\n";
    y = Y0;
    cout << "y0 = " << y << endl;

    for (int i = 0; i < n; i++) {
        y = linear(y, u);
        cout << "y" << i+1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель:\n";
    double yt = Y0;
    double yt1 = Y0;
    cout << "y0 = " << yt << endl;

    for (int i = 0; i < n; i++) {
        double new_y = nonlinear(yt, yt1, u, u);
        yt1 = yt;
        yt = new_y;
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    return 0;
}
