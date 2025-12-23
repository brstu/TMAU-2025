#include <iostream>
#include <cmath>
#include <array>
using std::cout;
using std::endl;

//constants
const int n = 10;
const double a_lin = 0.8;
const double b_lin = 0.2;
const double a_nonlin = 0.7;
const double b_nonlin = 0.1;
const double c_nonlin = 0.3;
const double d_nonlin = 0.05;
const double Y0 = 20.0;

double linear(double yt, double ut) {
    return a_lin * yt + b_lin * ut;
}

double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a_nonlin * yt - b_nonlin * pow(yt_1, 2) + c_nonlin * ut + d_nonlin * sin(ut_1);
}

int main() {
    std::array<double, n> u = { 0, 0, 0, 0, 0, 5, 5, 5, 5, 5 };

    cout << "Lin Mod" << endl;
    cout << "y0 = " << Y0 << endl;
    double yt_lin = Y0;
    for (int i = 0; i < n; i++) {
        yt_lin = linear(yt_lin, u[i]);
        cout << "y" << i + 1 << " = " << yt_lin << endl;
    }

    cout << "\nNonlin Mod" << endl;
    cout << "y0 = " << Y0 << endl;
    double yt_nonlin = Y0;
    double yt_prev = Y0;
    for (int i = 0; i < n; i++) {
        double ut = u[i];
        double ut_prev = (i == 0) ? 0 : u[i - 1];
        double yt_new = nonlinear(yt_nonlin, yt_prev, ut, ut_prev);
        cout << "y" << i + 1 << " = " << yt_new << endl;
        yt_prev = yt_nonlin;
        yt_nonlin = yt_new;
    }

    // Step response demonstration
    cout << "\nStep Response" << endl;
    cout << "y0 = 0" << endl;
    double yt_step = 0;
    for (int i = 0; i < 5; i++) {
        yt_step = linear(yt_step, 1.0);
        cout << "y" << i + 1 << " = " << yt_step << endl;
    }

    return 0;
}
