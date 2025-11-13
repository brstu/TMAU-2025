#include <iostream>
#include <cmath>
#include <array>

// Константы системы
const int TIME_STEPS = 10;
const double PARAM_A = 0.99;
const double PARAM_B = 0.01;
const double PARAM_C = 0.5;
const double PARAM_D = 0.1;
const double INITIAL_Y = 18;

// Линейная модель системы
double linearModel(double currentY, double inputU) {
    return PARAM_A * currentY + PARAM_B * inputU;
}

// Нелинейная модель системы
double nonlinearModel(double yt, double yt_1, double ut, double ut_1) {
    return PARAM_A * yt - PARAM_B * std::pow(yt_1, 2) + PARAM_C * ut + PARAM_D * std::sin(ut_1);
}

int main() {
    // Входные воздействия - используем std::array вместо C-style массива
    std::array<double, TIME_STEPS> inputSequence = {5, 7, 6, 5, 7, 6, 5, 7, 6, 5};
    
    // Моделирование линейной системы
    std::cout << "Линейная модель:" << std::endl;
    std::cout << "y0 = " << INITIAL_Y << std::endl;
    
    double currentY = INITIAL_Y;
    for (int step = 0; step < TIME_STEPS; step++) {
        currentY = linearModel(currentY, inputSequence[step]);
        std::cout << "y" << step + 1 << " = " << currentY << std::endl;
    }
    
    std::cout << std::endl;
    
    // Моделирование нелинейной системы
    std::cout << "Нелинейная модель:" << std::endl;
    std::cout << "y0 = " << INITIAL_Y << std::endl;
    
    double previousY = INITIAL_Y;
    currentY = INITIAL_Y;
    
    for (int step = 0; step < TIME_STEPS; step++) {
        double currentU = inputSequence[step];
        double previousU = (step == 0) ? inputSequence[0] : inputSequence[step - 1];
        
        double newY = nonlinearModel(currentY, previousY, currentU, previousU);
        std::cout << "y" << step + 1 << " = " << newY << std::endl;
        
        previousY = currentY;
        currentY = newY;
    }
    
    return 0;
}
