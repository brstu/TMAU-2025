#pragma once
#include <vector>

class TemperatureModel {
public:
    static const int STEPS = 10;
    static const double A;
    static const double B; 
    static const double C;
    static const double D;

    static double calcLinear(double currentY, double inputU);
    static double calcNonlinear(double currentY, double prevY, double inputU, double prevU);
    static bool validateInput(double temperature);
    static bool validateInputArray(const std::vector<double>& inputs);
    static void calculateLinearModel(double initialTemp, const std::vector<double>& inputs, std::vector<double>& results);
    static void calculateNonlinearModel(double initialTemp, const std::vector<double>& inputs, std::vector<double>& results);
};