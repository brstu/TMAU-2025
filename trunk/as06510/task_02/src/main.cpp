#include <iostream>
#include <array>
#include "func.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    const array<double, steps> control = {
        5, 7, 6, 5, 7, 6, 5, 7, 6, 5
    };

    cout << "Линейная модель" << endl;
    cout << "y0 = " << yStart << endl;

    double y = yStart;
    for (int i = 0; i < steps; i++) {
        y = linearModel(y, control[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "y0 = " << yStart << endl;

    y = yStart;
    double yPrev = yStart;

    for (int i = 0; i < steps - 1; i++) {
        y = nonlinearModel(y, yPrev, control[i + 1], control[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    return 0;
}
