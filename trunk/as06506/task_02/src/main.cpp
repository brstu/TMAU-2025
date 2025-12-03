#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    double U[N] = { 4, 6, 5, 4, 6, 5, 4, 6, 5, 4 };

    cout << "Линейная модель:" << endl;
    cout << "y0 = " << Y_START << endl;

    double y = Y_START;
    for (int i = 0; i < N; i++) {
        y = linearModel(y, U[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель:" << endl;
    cout << "y0 = " << Y_START << endl;

    double y_prev = Y_START;
    double y_curr = Y_START;

    for (int i = 0; i < N - 1; i++) {
        double y_next = nonlinearModel(y_curr, y_prev, U[i + 1], U[i]);
        cout << "y" << i + 1 << " = " << y_next << endl;

        y_prev = y_curr;
        y_curr = y_next;
    }

    return 0;
}
