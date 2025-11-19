#include <iostream>
#include "functions.h"

using std::cout;
using std::endl;


int main() {
    double y;

    cout << "Линейная модель:\n";
    y = Y0;
    cout << "y0 = " << y << endl;

    for (int i = 0; i < n; i++) {
        y = linear(y, u);
        cout << "y" << i + 1 << " = " << y << endl;
    }

    cout << "\nНелинейная модель:\n";
    double yt = Y0;
    double yt1 = Y0;
    cout << "y0 = " << yt << endl;

    for (int i = 0; i < n; i++) {
        double new_y = nonlinear(yt, yt1, u, u);
        yt1 = yt;
        yt = new_y;
        cout << "y" << i + 1 << " = " << yt << endl;
    }

    return 0;
}
