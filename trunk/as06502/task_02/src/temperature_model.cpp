#include "temperature_model.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>

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

bool TemperatureModel::validateInputArray(const std::vector<double>& inputs) {
    if (inputs.empty()) return false;
    
    return std::all_of(inputs.begin(), inputs.end(), validateInput);
}

void TemperatureModel::calculateLinearModel(double initialTemp, const std::vector<double>& inputs, std::vector<double>& results) {
    if (!validateInput(initialTemp) || !validateInputArray(inputs) || inputs.size() > STEPS) {
        throw std::invalid_argument("Invalid input parameters for linear model");
    }
    
    results.resize(inputs.size());
    auto prevTemperature = initialTemp;
    
    for (auto t = 0; t < inputs.size(); ++t) {
        results[t] = calcLinear(prevTemperature, inputs[t]);
        prevTemperature = results[t];
    }
}

void TemperatureModel::calculateNonlinearModel(double initialTemp, const std::vector<double>& inputs, std::vector<double>& results) {
    if (!validateInput(initialTemp) || !validateInputArray(inputs) || inputs.size() > STEPS) {
        throw std::invalid_argument("Invalid input parameters for nonlinear model");
    }
    
    if (inputs.size() < 2) {
        throw std::invalid_argument("Nonlinear model requires at least 2 steps");
    }
    
    results.resize(inputs.size());
    auto currentY = initialTemp;
    auto previousY = initialTemp;
    results[0] = initialTemp;
    
    for (auto t = 1; t < inputs.size(); ++t) {
        auto uCurr = inputs[t];
        auto uPrev = inputs[t-1];
        
        results[t] = calcNonlinear(currentY, previousY, uCurr, uPrev);
        previousY = currentY;
        currentY = results[t];
    }
}