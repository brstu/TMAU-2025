#ifndef MODEL_FUNCTIONS_H
#define MODEL_FUNCTIONS_H

#include <cmath>

namespace Constants {
    const double A = 0.2;
    const double B = 0.02;
    const double C = 0.03;
    const double D = 0.04;
}

double calcLinear(double currentY, double inputU);
double calcNonlinear(double currentY, double prevY, double inputU, double prevU);

#endif