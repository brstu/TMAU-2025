#include <iostream>
#include <cmath>
using namespace std;

int n = 10;
const double a = 0.9;
const double b = 0.001;
const double c = 0.4;
const double d = 0.1;
double ini_val = 10;

double linear(double yt, double ut) {
    return a * yt + b * ut;
}

double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a * yt - b * pow(yt_1, 2) + c * ut + d * sin(ut_1);
}

int main() {
    setlocale(LC_ALL, "RU");
    cout << "Линейная модель" << endl;
    cout << "y0 = " << ini_val << endl;
    double u[10] = { 10,8,12,9,11,10,8,12,9,11 };
    double yt = ini_val, yt_1 = ini_val;

    for (int i = 0; i < n; i++) {
        yt = linear(yt, u[i]);
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    cout << "\n";
    yt_1 = yt = ini_val;
    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << ini_val << endl;

    for (int i = 0; i < n - 1; i++) {
        double temp = yt;
        yt = nonlinear(yt, yt_1, u[i + 1], u[i]);
        yt_1 = temp;
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    system("pause");
    return 0;
}