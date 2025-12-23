#include <iostream>
#include <cmath>
#include <vector>
#include "func.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    vector<double> u = { 10.0, 8.0, 12.0, 9.0, 11.0, 10.0, 8.0, 12.0, 9.0, 11.0 };
    const size_t steps = u.size();  // Исправлено: size_t вместо int

    cout << "Линейная модель" << endl;
    cout << "Начальное значение: " << ini_val << endl;

    double yt = ini_val;
    for (size_t i = 0; i < steps; i++) {  // Исправлено: size_t вместо int
        yt = linear(yt, u[i]);
        cout << "Шаг " << i + 1 << ": y = " << yt << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "Начальное значение: " << ini_val << endl;

    double yt_prev = ini_val;
    yt = ini_val;

    for (size_t i = 0; i < steps - 1; i++) {  // Исправлено: size_t вместо int
        double current_yt = yt;
        yt = nonlinear(yt, yt_prev, u[i + 1], u[i]);
        yt_prev = current_yt;
        cout << "Шаг " << i + 1 << ": y = " << yt << endl;
    }

    cout << "\nРасчет завершен. Для выхода нажмите Enter...";
    cin.ignore();
    cin.get();
    
    return 0;
}
