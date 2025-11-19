#pragma once

class TemperatureModel {
public:
    static const int STEPS = 10;
    static const double A;
    static const double B; 
    static const double C;
    static const double D;

    // y(t) = A * y(t-1) + B * u(t)
    static double calcLinear(double currentY, double inputU);
    
    // y(t) = A * y(t-1) - B * y(t-1)^2 + C * u(t) + D * sin(u(t-1))
    static double calcNonlinear(double currentY, double prevY, double inputU, double prevU);
    
    static bool validateInput(double temperature);
    static bool validateInputArray(const double inputs[], int size);
    
    static void calculateLinearModel(double initialTemp, const double inputs[], int size, double results[]);
      
    static void calculateNonlinearModel(double initialTemp, const double inputs[], int size, double results[]);
};