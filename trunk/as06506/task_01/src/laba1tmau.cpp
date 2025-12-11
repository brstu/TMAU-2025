#include <iostream>
#include <cmath>
#include <array>

using namespace std;

const int N = 10;         
const double A = 0.97;    
const double B = 0.015;   
const double C = 0.45;    
const double D = 0.12;    
const double Y_start = 20.0;  // Сделано константой

double linearModel(double y, double u) {
    return A * y + B * u;
}

double nonlinearModel(double y_curr, double y_prev, double u_curr, double u_prev) {
    return A * y_curr - B * pow(y_prev, 2) + C * u_curr + D * sin(u_prev);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // Заменяем C-массив на std::array
    array<double, N> U = { 4.0, 6.0, 5.0, 4.0, 6.0, 5.0, 4.0, 6.0, 5.0, 4.0 }; 

    cout << "Линейная модель:" << endl;
    cout << "y0 = " << Y_start << endl;

    double y = Y_start;
    for (int i = 0; i < N; i++) {
        y = linearModel(y, U[i]);  // Обращение к элементам такое же
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель:" << endl;
    cout << "y0 = " << Y_start << endl;

    double y_prev = Y_start;
    double y_curr = Y_start;

    for (int i = 0; i < N - 1; i++) {
        double y_next = nonlinearModel(y_curr, y_prev, U[i + 1], U[i]);
        cout << "y" << i + 1 << " = " << y_next << endl;
        y_prev = y_curr;
        y_curr = y_next;
    }

    cout << "\nДля завершения нажмите Enter...";
    cin.get(); 
    return 0;
}
