#include <iostream>
#include <cmath>
#include <array>

constexpr std::size_t N = 10;
constexpr double COEFF_A = 0.7;
constexpr double COEFF_B = 0.05;
constexpr double COEFF_C = 0.3;
constexpr double COEFF_D = 0.2;
constexpr double INITIAL_VALUE = 15.0;

const std::array<double, N> inputSequence{
    12.0, 9.0, 14.0, 11.0, 13.0,
    10.0, 8.0, 15.0, 12.0, 11.0
};

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
    // Линейная модель
    std::cout << "Линейная модель" << std::endl;
    std::cout << "y0 = " << INITIAL_VALUE << std::endl;

    double currentY = INITIAL_VALUE;

    for (std::size_t step = 0; step < N; ++step) {
        currentY = linearModel(currentY, inputSequence[step]);
        std::cout << "y" << step + 1 << " = " << currentY << std::endl;
    }

    // Нелинейная модель
    std::cout << "Нелинейная модель" << std::endl;
    std::cout << "y0 = " << INITIAL_VALUE << std::endl;

    double previousY = INITIAL_VALUE;
    currentY = INITIAL_VALUE;

    for (std::size_t step = 0; step < N - 1; ++step) {
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
