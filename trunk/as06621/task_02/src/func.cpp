#include "func.h"

// Линейная модель
double linear(double currentTemperature, double controlSignal) {
    return LINEAR_A * currentTemperature + LINEAR_B * controlSignal;
}

// Нелинейная модель
double nonlinear(double currentTemperature, double previousTemperature,
                 double currentControlSignal, double previousControlSignal) {
    return NONLINEAR_A * currentTemperature 
           - NONLINEAR_B * (previousTemperature * previousTemperature) 
           + NONLINEAR_C * currentControlSignal 
           + NONLINEAR_D * std::sin(previousControlSignal);
}