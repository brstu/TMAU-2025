#include <iostream>
#include <vector>
#include <cmath>
#include "model.h"
using namespace std;

int main() {
    double a = 0.8;
    double b = 0.2;
    double c = 0.1;
    double d = 0.05;

    int N = 20; 

    vector<double> y(N + 1, 0.0); 
    vector<double> u(N + 1, 0.0); 

    
    for (int t = 0; t <= N; t++) {
        if (t < 5) u[t] = 0.0;
        else u[t] = 1.0; 
    }

    cout << "linear model" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], a, b);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    fill(y.begin(), y.end(), 0.0);

    cout << "\n non linear model" << endl;
    for (int t = 1; t < N; t++) {
        y[t + 1] = nonlinear_model(y[t], y[t - 1], u[t], u[t - 1], a, b, c, d);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    return 0;
}