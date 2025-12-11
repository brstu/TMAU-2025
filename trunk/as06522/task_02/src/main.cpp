#include <iostream>
#include <cmath>
#include <array>
#include "func.h"

using std::cout;
using std::endl;

int main() {
    setlocale(LC_ALL, "rus");

    cout << "Линейная модель" << endl;
    cout << "y0 = " << INITIAL_VALUE << endl;

    std::array<double, TIME_STEPS> controlInputs = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
    double currentValue = INITIAL_VALUE;

    for (int step = 0; step < TIME_STEPS; step++) {
        currentValue = linearModel(currentValue, controlInputs[step]);
        cout << "y" << step + 1 << " = " << currentValue << endl;
    }

    cout << "\nНелинейная модель" << endl;
    cout << "y0 = " << INITIAL_VALUE << endl;

    double previousValue = INITIAL_VALUE;
    currentValue = INITIAL_VALUE;

    for (int step = 0; step < TIME_STEPS; step++) {
        double currentU = controlInputs[step];
        double previousU = (step == 0 ? controlInputs[0] : controlInputs[step - 1]);

        double newValue = nonlinearModel(currentValue, previousValue, currentU, previousU);
        cout << "y" << step + 1 << " = " << newValue << endl;

        previousValue = currentValue;
        currentValue = newValue;
    }

    return 0;
}
