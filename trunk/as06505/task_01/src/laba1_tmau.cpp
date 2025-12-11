#include <iostream>
#include <cmath>
#include <vector>  
#include <array>  

using namespace std;
const int n = 10;
const double a = 0.9;
const double b = 0.001;
const double c = 0.4;
const double d = 0.1;
const double ini_val = 10.0;

const std::array<double, n> u = { 10.0, 8.0, 12.0, 9.0, 11.0, 10.0, 8.0, 12.0, 9.0, 11.0 };

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
    
    double yt = ini_val;
    
    double yt_prev = ini_val;

    // Линейная модель
    for (int i = 0; i < n; i++) {
        yt = linear(yt, u[i]);
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    cout << "\n";
    
    yt = ini_val;
    yt_prev = ini_val;
    
    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << ini_val << endl;
    
    for (int i = 0; i < n - 1; i++) {
        double temp = yt;
        yt = nonlinear(yt, yt_prev, u[i + 1], u[i]);
        yt_prev = temp;
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    cout << "\nНажмите Enter для выхода...";
    cin.get();
    
    return 0;
}
