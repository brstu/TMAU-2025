#pragma once
#include <cmath>

namespace ModelConstants {
    // Коэффициенты для линейной модели
    constexpr double LINEAR_A = 0.9;
    constexpr double LINEAR_B = 0.01;
    
    // Коэффициенты для нелинейной модели
    constexpr double NONLINEAR_A = 0.9;
    constexpr double NONLINEAR_B = 0.01;
    constexpr double NONLINEAR_C = 0.15;
    constexpr double NONLINEAR_D = 0.05;
    
    constexpr double ZERO_PREV_INPUT = 0.0;
}

namespace TemperatureModels {
    // Линейная модель
    double computeLinearModel(double currentTemperature, double controlSignal);
    
    // Нелинейная модель
    double computeNonlinearModel(double currentTemperature, 
                                 double previousTemperature,
                                 double currentControlSignal, 
                                 double previousControlSignal);
}