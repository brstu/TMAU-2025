#include "func.h"
#include <cmath>


const double temperatureCoeff = 0.6;
const double prevTemperatureCoeff = 0.3;
const double warmCoeff = 0.8;
const double prevWarmCoeffSin = 0.5;

double linearmodel(double inputtemperature, double inputwarm) {
    return temperatureCoeff * inputtemperature + prevTemperatureCoeff * inputwarm;
}

double nonlinearmodel(double inputtemperature, double prevtemperature, double inputwarm, double prevwarm) {
    return temperatureCoeff * inputtemperature
        - prevTemperatureCoeff * pow(prevtemperature, 2)
        + warmCoeff * inputwarm
        + prevWarmCoeffSin * sin(prevwarm);
}

double updateWarm(double baseWarm, int t) {
    return baseWarm + 0.1 * sin(t);
}
