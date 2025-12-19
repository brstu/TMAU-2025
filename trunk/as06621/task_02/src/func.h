#pragma once
#include <cmath>

// Коэффициенты моделей
constexpr double LINEAR_A = 0.9;
constexpr double LINEAR_B = 0.01;
constexpr double NONLINEAR_A = 0.9;
constexpr double NONLINEAR_B = 0.01;
constexpr double NONLINEAR_C = 0.15;
constexpr double NONLINEAR_D = 0.05;

constexpr double ZERO_PREV_INPUT = 0.0;

// Линейная модель
double linear(double currentTemperature, double controlSignal);

// Нелинейная модель
double nonlinear(double currentTemperature, double previousTemperature,
                 double currentControlSignal, double previousControlSignal);