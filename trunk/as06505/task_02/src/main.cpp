#include <iostream>
#include <cmath>
#include <array>
#include "func.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    const array<double, N> u = { 10.0, 8.0, 12.0, 9.0, 11.0, 10.0, 8.0, 12.0, 9.0, 11.0 };

    cout << "Линейная модель" << endl;
    cout << "y0 = " << ini_val << endl;

    double yt = ini_val;
    for (int i = 0; i < N; i++) {
        yt = linear(yt, u[i]);
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "y0 = " << ini_val << endl;

    double yt_prev = ini_val;
    yt = ini_val;

    for (int i = 0; i < N - 1; i++) {
        double temp = yt;
        yt = nonlinear(yt, yt_prev, u[i + 1], u[i]);
        yt_prev = temp;
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    cout << "\nНажмите Enter для выхода...";
    cin.get();
    return 0;
}
