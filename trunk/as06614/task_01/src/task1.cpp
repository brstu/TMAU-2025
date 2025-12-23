#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>

using namespace std;

vector<double> linear_model(double a, double b, const vector<double>& u, double y0) {
    vector<double> y(u.size() + 1);
    y[0] = y0;
    for (size_t t = 0; t < u.size(); ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

vector<double> nonlinear_model(double a, double b, double c, double d,
                               const vector<double>& u,
                               double y0, double y_minus1) {
    vector<double> y(u.size() + 1);
    y[0] = y0;
    if (u.size() >= 1) {
        y[1] = a * y[0] - b * pow(y_minus1, 2) + c * u[0] + d * sin(u[0]);
    }
    for (size_t t = 1; t < u.size(); ++t) {
        y[t + 1] = a * y[t] - b * pow(y[t - 1], 2) + c * u[t] + d * sin(u[t - 1]);
    }
    return y;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    cout << "Моделирование температуры объекта с заданными параметрами\n" << endl;
    
    double a = 0.8;
    double b = 0.2;
    double c = 0.3;
    double d = 0.1;
    double y0 = 20.0;
    double y_minus1 = 18.0;
    vector<double> u = {10, 12, 15, 14, 13};
    
    cout << "Параметры модели:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    cout << "d = " << d << endl;
    cout << "y0 = " << y0 << endl;
    cout << "y_{-1} = " << y_minus1 << endl;
    cout << "Входные воздействия u: ";
    for (size_t i = 0; i < u.size(); ++i) {
        cout << u[i] << " ";
    }
    cout << "\n" << endl;
    
    cout << "ЛИНЕЙНАЯ МОДЕЛЬ" << endl;
    vector<double> y_linear = linear_model(a, b, u, y0);
    cout << "Шаг\tТемпература y(τ)" << endl;
    for (size_t t = 0; t < y_linear.size(); ++t) {
        cout << t << "\t" << y_linear[t] << endl;
    }
    
    cout << "\nНЕЛИНЕЙНАЯ МОДЕЛЬ" << endl;
    vector<double> y_nonlinear = nonlinear_model(a, b, c, d, u, y0, y_minus1);
    cout << "Шаг\tТемпература y(τ)" << endl;
    for (size_t t = 0; t < y_nonlinear.size(); ++t) {
        cout << t << "\t" << y_nonlinear[t] << endl;
    }
    
    cout << "\nНажмите Enter для выхода...";
    cin.get();
    
    return 0;
}