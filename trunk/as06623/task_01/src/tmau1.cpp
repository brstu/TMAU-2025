#include <iostream>
#include <cmath>

const int N = 10;
const double COEFF_A = 0.7;
const double COEFF_B = 0.05;
const double COEFF_C = 0.3;
const double COEFF_D = 0.2;
const double INITIAL_VALUE = 15.0;

// Линейная модель: y_{k+1} = a * y_k + b * u_k
double linearModel(double currentY, double inputU) {
    return COEFF_A * currentY + COEFF_B * inputU;
}

// Нелинейная модель:
// y_{k+1} = a * y_k - b * y_{k-1}^2 + c * u_k + d * sin(u_{k-1})
double nonlinearModel(double currentY,
                      double previousY,
                      double currentU,
                      double previousU) {
    return COEFF_A * currentY
         - COEFF_B * previousY * previousY
         + COEFF_C * currentU
         + COEFF_D * std::sin(previousU);
}

int main() {
    const double inputSequence[N] = {
        12.0, 9.0, 14.0, 11.0, 13.0,
        10.0, 8.0, 15.0, 12.0, 11.0
    };

    // Линейная модель
    std::cout << "Линейная модель" << std::endl;
    std::cout << "y0 = " << INITIAL_VALUE << std::endl;

    double currentY = INITIAL_VALUE;

    for (int step = 0; step < N; ++step) {
        currentY = linearModel(currentY, inputSequence[step]);
        std::cout << "y" << step + 1 << " = " << currentY << std::endl;
    }

    // Нелинейная модель
    std::cout << "Нелинейная модель" << std::endl;
    std::cout << "y0 = " << INITIAL_VALUE << std::endl;

    double previousY = INITIAL_VALUE;
    currentY = INITIAL_VALUE;

    for (int step = 0; step < N - 1; ++step) {
        double temporaryY = currentY;
        currentY = nonlinearModel(
            currentY,
            previousY,
            inputSequence[step + 1],
            inputSequence[step]
        );
        previousY = temporaryY;

        std::cout << "y" << step + 1 << " = " << currentY << std::endl;
    }

    return 0;
}
