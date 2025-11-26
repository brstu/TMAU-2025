#include <iostream>
#include <array>
#include "func.h"
using std::cout;
using std::endl;



int main() {
    cout << "Linear model" << endl;
    cout << "y0 = " << Y0 << endl;
    std::array<double, 10> u = { 5,7,6,5,7,6,5,7,6,5 };
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
