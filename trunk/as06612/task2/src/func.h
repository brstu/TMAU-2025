#pragma once
#include <cmath>

// Константы модели
extern const double TEMP_COEFF;
extern const double PREV_TEMP_COEFF;
extern const double WARM_COEFF;
extern const double PREV_WARM_COEFF;
extern const double WARM_MODULATION;

// Функции модели
double computeLinearModel(double temperature, double warm);
double computeNonLinearModel(double current_temp, double prev_temp,
                             double current_warm, double prev_warm);
double adjustWarmInput(double base_warm, int time_step);