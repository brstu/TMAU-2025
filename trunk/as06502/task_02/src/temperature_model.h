#pragma once

class TemperatureModel {
public:
    static const int STEPS = 10;  // Можно оставить так для целых чисел
    static const double A;
    static const double B; 
    static const double C;
    static const double D;

    // Линейная модель: y(t) = A * y(t-1) + B * u(t)
    static double calcLinear(double currentY, double inputU);
    
    // Нелинейная модель: y(t) = A * y(t-1) - B * y(t-1)^2 + C * u(t) + D * sin(u(t-1))
    static double calcNonlinear(double currentY, double prevY, double inputU, double prevU);
    
    // Проверка корректности входных данных
    static bool validateInput(double temperature);
    static bool validateInputArray(const double inputs[], int size);
    
    // Расчет всей последовательности для линейной модели
    static void calculateLinearModel(double initialTemp, const double inputs[], int size, double results[]);
    
    // Расчет всей последовательности для нелинейной модели  
    static void calculateNonlinearModel(double initialTemp, const double inputs[], int size, double results[]);
};