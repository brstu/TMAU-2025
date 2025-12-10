#include <iostream>
#include <cmath>
#include <array>
#include "func.h"

int main() {
    std::array<double, TIME_STEPS> inputSequence = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };

    std::cout << "Линейная модель:" << std::endl;
    std::cout << "y0 = " << INITIAL_Y << std::endl;

    double currentY = INITIAL_Y;
    for (int step = 0; step < TIME_STEPS; step++) {
        currentY = linearModel(currentY, inputSequence[step]);
        std::cout << "y" << step + 1 << " = " << currentY << std::endl;
    }

    std::cout << "\nНелинейная модель:" << std::endl;
    std::cout << "y0 = " << INITIAL_Y << std::endl;

    double previousY = INITIAL_Y;
    currentY = INITIAL_Y;

    for (int step = 0; step < TIME_STEPS; step++) {
        double currentU = inputSequence[step];
        double previousU = (step == 0 ? inputSequence[0] : inputSequence[step - 1]);

        double newY = nonlinearModel(currentY, previousY, currentU, previousU);
        std::cout << "y" << step + 1 << " = " << newY << std::endl;

        previousY = currentY;
        currentY = newY;
    }

    return 0;
}
