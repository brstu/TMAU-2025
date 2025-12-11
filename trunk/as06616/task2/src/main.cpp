#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

int main() {
    int time = 0;
    double inputtemperature = 0;
    double inputwarm = 0;

    cout << "Введите количество шагов моделирования, начальное значение y0 и управляющее воздействие u0: ";
    cin >> time >> inputtemperature >> inputwarm;

    double prevtemperature = inputtemperature;
    double prevwarm = inputwarm;

    cout << "\nЛинейная модель:\n";
    double y_linear = inputtemperature;
    for (int t = 1; t <= time; t++) {
        y_linear = linearmodel(y_linear, inputwarm);
        cout << "Шаг " << t << ": y = " << y_linear << endl;
    }

    cout << "\nНелинейная модель:\n";
    double y_nl = inputtemperature;
    for (int t = 1; t <= time; t++) {
        double currentWarm = updateWarm(inputwarm, t);
        double next = nonlinearmodel(y_nl, prevtemperature, currentWarm, prevwarm);
        cout << "Шаг " << t << ": y = " << next << endl;
        prevtemperature = y_nl;
        y_nl = next;
        prevwarm = currentWarm;
    }

    return 0;
}
