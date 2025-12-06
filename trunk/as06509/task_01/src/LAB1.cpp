#include <iostream>
#include <vector>
#include <cmath> 

using namespace std;

struct Constants{
    const int n = 10;  

    const double a = 1.2;
    const double b = 0.01;
    const double c = 0.75;
    const double d = 0.03;
};

void linear(const Constants &con, vector<double> &u) {
    vector<double> y(con.n + 1, 0.0); 
    y[0] = 25;

    for (int t = 0; t < con.n; ++t) {
        y[t + 1] = con.a * y[t] + con.b * u[t];
    }

    cout << "Linear:\n";
    for (int t = 0; t <= con.n; ++t) {
        cout << "y" << t << ": " << y[t] << endl;
    }
}

void Nonlinear(const Constants &con, vector<double> &u) {
    vector<double> y(con.n + 1, 0.0); 
    y[0] = 25;
    y[1] = y[0];

    for (int t = 1; t < con.n; ++t) {
        y[t + 1] = con.a * y[t] - con.b * pow(y[t - 1], 2) + con.c * u[t] + con.d * sin(u[t - 1]);
    }

    cout << "\nNonlinear:\n";
    for (int t = 0; t <= con.n; ++t) {
        cout << "y" << t << ": " << y[t] << endl;
    }
}

int main() {
    Constants con;
    vector<double> u(10, 4.0); 

    linear(con, u);
    Nonlinear(con, u);

    return 0;
}
