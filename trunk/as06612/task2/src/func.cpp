#include "func.h"

// Определение констант
const double TEMP_COEFF = 0.6;
const double PREV_TEMP_COEFF = 0.3;
const double WARM_COEFF = 0.8;
const double PREV_WARM_COEFF = 0.5;
const double WARM_MODULATION = 0.1;

// Определение функций
double computeLinearModel(double temperature, double warm) {
    return TEMP_COEFF * temperature + PREV_TEMP_COEFF * warm;
}

double computeNonLinearModel(double current_temp, double prev_temp,
                             double current_warm, double prev_warm) {
    return TEMP_COEFF * current_temp
           - PREV_TEMP_COEFF * pow(prev_temp, 2)
           + WARM_COEFF * current_warm
           + PREV_WARM_COEFF * sin(prev_warm);
}

double adjustWarmInput(double base_warm, int time_step) {
    return base_warm + WARM_MODULATION * sin(time_step);
}