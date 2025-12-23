#include "func.h"

double linearModel(double currentY, double inputU) {
    return PARAM_A * currentY + PARAM_B * inputU;
}

double nonlinearModel(double yt, double yt_1, double ut, double ut_1) {
    return PARAM_A * yt - PARAM_B * pow(yt_1, 2) + PARAM_C * ut + PARAM_D * sin(ut_1);
}
