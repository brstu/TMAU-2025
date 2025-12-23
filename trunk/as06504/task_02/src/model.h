#pragma once
#include <cmath>

struct LinearCfg {
    double alpha;
    double beta;
};

struct NonlinearCfg {
    double alpha;
    double beta;
    double gamma;
    double delta;
};

double linearStep(double prevY, double prevU, const LinearCfg& cfg);
double nonlinearStep(double prevY, double prevY2, double prevU, double prevU2, const NonlinearCfg& cfg);
