#include <iostream>
#include <array>
#include "func.h"
using std::cout;
using std::endl;

int main() {
    std::array<double, N> u = { 2.0, 4.0, 3.0, 5.0, 4.0, 6.0, 3.0, 5.0 };

    double y = Y_START;
    double y_prev = Y_START;

    cout << "Линейная модель" << endl;
    cout << "y0 = " << Y_START << endl;

    for (size_t i = 0; i < u.size(); i++) {
        y = linearModel(y, u[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "y0 = " << Y_START << endl;

    y = y_prev = Y_START;
    for (size_t i = 0; i < u.size() - 1; i++) {
        double y_next = nonlinearModel(y, y_prev, u[i + 1], u[i]);
        cout << "y" << i + 1 << " = " << y_next << endl;

        y_prev = y;
        y = y_next;
    }

    return 0;
}
