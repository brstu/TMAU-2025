#pragma once
#include <cmath>

extern const double temperatureCoeff;
extern const double prevTemperatureCoeff;
extern const double warmCoeff;
extern const double prevWarmCoeffSin;

double linearmodel(double inputtemperature, double inputwarm);

double nonlinearmodel(double inputtemperature, double prevtemperature, double inputwarm, double prevwarm);

double updateWarm(double baseWarm, int t);