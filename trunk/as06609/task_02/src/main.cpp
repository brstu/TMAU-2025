#include <iostream>
#include "func.h"
using std::cout;
using std::endl;

int main() {
    double u[N] = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
    double y = Y_START;
    double y_prev = Y_START;

    cout << "Линейная модель" << endl;
    cout << "y0 = " << Y_START << endl;

    for (int i = 0; i < N; i++) {
        y = linearModel(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "y0 = " << Y_START << endl;

    y = y_prev = Y_START;
    for (int i = 0; i < N - 1; i++) {
        y = nonlinearModel(y, y_prev, u[i + 1], u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
        y_prev = y;
    }

    return 0;
}
