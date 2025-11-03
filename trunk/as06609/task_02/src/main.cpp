#include <iostream>
#include <array>
#include "func.h"
using std::cout;
using std::endl;

int main() {
    std::array<double, N> u = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
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
    for (size_t i = 0; i < u.size(); i++) {
        y_prev = y;
        double u_curr = u[i];
        double u_prev = (i == 0) ? u[0] : u[i - 1];
        y = nonlinearModel(y, y_prev, u_curr, u_prev);
        cout << "y" << i + 1 << " = " << y << endl;
    }
    return 0;
}
