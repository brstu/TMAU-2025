#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;

void runLinearModel() {
    double y = Y0;
    cout << "Линейная модель:\n";
    cout << "y0 = " << y << endl;

    for (int i = 0; i < n; i++) {
        y = linear(y, u);
        cout << "y" << i + 1 << " = " << y << endl;
    }
}

void runNonlinearModel() {
    double yt = Y0;
    double yt1 = Y0;
    cout << "\nНелинейная модель:\n";
    cout << "y0 = " << yt << endl;

    for (int i = 0; i < n; i++) {
        double new_y = nonlinear(yt, yt1, u, u);
        yt1 = yt;
        yt = new_y;
        cout << "y" << i + 1 << " = " << yt << endl;
    }
}

int main() {
    runLinearModel();
    runNonlinearModel();
    return 0;
}
