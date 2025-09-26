#include <iostream>
#include <cmath>
using std::cout;
using std::endl;
// constants
const int n = 10; // time steps
const double a = 0.99;
const double b = 0.01;
const double c = 0.5;
const double d = 0.1;
const double Y0 = 18;

// linear model
double linear(double yt, double ut) {
    return a * yt + b * ut;
}

// nonlinear model
double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a * yt - b * pow(yt_1, 2) + c * ut + d * sin(ut_1);
}

int main() { 
    cout << "Linear model" << endl;
    cout << "y0 = " << Y0 << endl;
    double u[n] = { 5,7,6,5,7,6,5,7,6,5 };
    double yt = Y0;
    for (int i = 0; i < n; i++) {
        yt = linear(yt, u[i]);
        cout << "y" << i + 1 << " = " << yt << endl;
    }
    cout << "\n";
    double yt_1 = Y0;
    yt = Y0;
    cout << "Nonlinear model" << endl;
    cout << "y0 = " << Y0 << endl;
    for (int i = 0; i < n; i++) {
        double ut = u[i];
        double ut_1 = (i == 0) ? u[0] : u[i - 1];
        double yt_new = nonlinear(yt, yt_1, ut, ut_1);
        cout << "y" << i + 1 << " = " << yt_new << endl;
        yt_1 = yt;
        yt = yt_new;
    }
    return 0;
}
