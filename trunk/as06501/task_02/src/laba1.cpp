#include <iostream>
#include <cmath>
#include "lab1.h"
using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");

    double u[N] = { 5,7,6,5,7,6,5,7,6,5 };

    cout << "Линейная модель:" << endl;
    cout << "y0 = " << start_value << endl;
    double y = start_value;
    for (int i = 0; i < N; i++) {
        y = linear(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }  // ← ДОБАВИТЬ закрывающую скобку

    cout << "\nНелинейная модель:" << endl;
    cout << "y0 = " << start_value << endl;
    double y_prev = start_value;
    double y_curr = start_value;
    for (int i = 0; i < N - 1; i++) {
        double y_next = nonlinear(y_curr, y_prev, u[i + 1], u[i]);
        cout << "y" << i + 1 << " = " << y_next << endl;
        y_prev = y_curr;
        y_curr = y_next;
    }

    std::cin.get();
    return 0;
}
