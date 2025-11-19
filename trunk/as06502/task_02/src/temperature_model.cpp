#include "temperature_model.h"
#include <cmath>
#include <stdexcept>

const double TemperatureModel::A = 0.2;
const double TemperatureModel::B = 0.02;
const double TemperatureModel::C = 0.03;
const double TemperatureModel::D = 0.04;


double TemperatureModel::calcLinear(double currentY, double inputU) {
    if (!validateInput(currentY) || !validateInput(inputU)) {
        throw std::invalid_argument("Invalid input parameters");
    }
    return (A * currentY) + (B * inputU);
}

double TemperatureModel::calcNonlinear(double currentY, double prevY, double inputU, double prevU) {
    if (!validateInput(currentY) || !validateInput(prevY) || 
        !validateInput(inputU) || !validateInput(prevU)) {
        throw std::invalid_argument("Invalid input parameters");
    }
    return (A * currentY) - (B * prevY * prevY) + (C * inputU) + D * sin(prevU);
}

bool TemperatureModel::validateInput(double temperature) {
    return !std::isnan(temperature) && 
           !std::isinf(temperature) &&
           temperature >= -100.0 && 
           temperature <= 1000.0;
}

bool TemperatureModel::validateInputArray(const double inputs[], int size) {
    if (size <= 0) return false;
    
    for (int i = 0; i < size; ++i) {
        if (!validateInput(inputs[i])) {
            return false;
        }
    }
    return true;
}

void TemperatureModel::calculateLinearModel(double initialTemp, const double inputs[], int size, double results[]) {
    if (!validateInput(initialTemp) || !validateInputArray(inputs, size) || size > STEPS) {
        throw std::invalid_argument("Invalid input parameters for linear model");
    }
    
    double prevTemperature = initialTemp;
    
    for (int t = 0; t < size; ++t) {
        results[t] = calcLinear(prevTemperature, inputs[t]);
        prevTemperature = results[t];
    }
}

void TemperatureModel::calculateNonlinearModel(double initialTemp, const double inputs[], int size, double results[]) {
    if (!validateInput(initialTemp) || !validateInputArray(inputs, size) || size > STEPS) {
        throw std::invalid_argument("Invalid input parameters for nonlinear model");
    }
    
    if (size < 2) {
        throw std::invalid_argument("Nonlinear model requires at least 2 steps");
    }
    
    double currentY = initialTemp;
    double previousY = initialTemp;
    results[0] = initialTemp; 
    
    for (int t = 1; t < size; ++t) {
        double uCurr = inputs[t];
        double uPrev = inputs[t-1];
        
        results[t] = calcNonlinear(currentY, previousY, uCurr, uPrev);
        previousY = currentY;
        currentY = results[t];
    }
}