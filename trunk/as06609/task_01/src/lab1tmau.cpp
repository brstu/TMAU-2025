#include <iostream>
#include <cmath>
#include <array>  

using namespace std;

const int N = 10;   
const double A = 0.99;
const double B = 0.01;
const double C = 0.5;
const double D = 0.1;
const double Y_START = 18.0;

double linearModel(double y, double u) {
    return A * y + B * u;
}

double nonlinearModel(double y, double y_prev, double u, double u_prev) {
    return A * y - B * pow(y_prev, 2) + C * u + D * sin(u_prev);
}

int main() {
    setlocale(LC_ALL, "Russian");

    array<double, N> u = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
    double y = Y_START;
    double y_prev = Y_START;

    cout << "Линейная модель" << endl;
    cout << "y0 = " << Y_START << endl;

    for (int i = 0; i < N; i++) {
        y = linearModel(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "y0 = " << Y_START << endl;

    y = y_prev = Y_START;
    for (int i = 0; i < N - 1; i++) {
        y = nonlinearModel(y, y_prev, u[i + 1], u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cin.get();
    return 0;
}
