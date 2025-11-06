#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int N = 10;
const double a = 0.85;      
const double b = 0.05;       
const double c = 0.35;       
const double d = 0.12;      
double start_value = 10.0;   

double linear(double y, double u) {
    return a * y + b * u;
}

double nonlinear(double yt, double yt1, double ut, double ut1) {
    return a * yt - b * pow(yt1, 1.5) + c * ut + d * sin(ut1); 
}

int main() {
    setlocale(LC_ALL, "Russian");

    double u[N] = { 3.0, 5.0, 4.0, 6.0, 5.0, 7.0, 4.0, 6.0, 5.0, 4.0 };

    cout << fixed << setprecision(3);
    
    cout << "Линейная модель:" << endl;
    cout << "y0 = " << start_value << endl;
    double y = start_value;
    for (int i = 0; i < N; i++) {
        y = linear(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель:" << endl;
    cout << "y0 = " << start_value << endl;
    double y_prev = start_value;
    double y_curr = start_value;
    
   
    double y_next = nonlinear(y_curr, y_prev, u[0], u[0]);
    cout << "y1 = " << y_next << endl;
    y_prev = y_curr;
    y_curr = y_next;
    

    for (int i = 1; i < N - 1; i++) {
        y_next = nonlinear(y_curr, y_prev, u[i], u[i-1]);
        cout << "y" << i + 1 << " = " << y_next << endl;
        y_prev = y_curr;
        y_curr = y_next;
    }

    cout << "\nНажмите Enter для выхода...";
    cin.get();
    return 0;
}
