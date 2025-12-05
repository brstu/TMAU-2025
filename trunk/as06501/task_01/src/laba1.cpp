#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>
#include <vector>
using namespace std;

const int N = 8;  
const double a = 0.85;      
const double b = 0.05;       
const double c = 0.35;       
const double d = 0.12;      
const double start_value = 10;  


double linear(double y, double u) {
    return a * y + b * u;
}

double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * pow(yt1, 2) + c * ut + d * sin(ut1);  
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::array<double, N> u = { 2.0, 4.0, 3.0, 5.0, 4.0, 6.0, 3.0, 5.0 };

    cout << fixed << setprecision(4);  
    
    cout << "=== МОДЕЛЬ 1 (Задача 1) ===" << endl;
    cout << "Линейная модель:" << endl;
    cout << "y0 = " << start_value << endl;
    
    double y = start_value;
    for (int i = 0; i < N; i++) {
        y = linear(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель:" << endl;
    cout << "y0 = " << start_value << endl;
    
    vector<double> results;
    results.push_back(start_value);
    
    for (int i = 0; i < N - 1; i++) {
        double y_next = nonlinear(results[i], (i > 0 ? results[i-1] : start_value), u[i], u[i]);
        results.push_back(y_next);
        cout << "y" << i + 1 << " = " << y_next << endl;
    }

    cout << "\nРасчет завершен.";
    cin.get();
    return 0;
}
