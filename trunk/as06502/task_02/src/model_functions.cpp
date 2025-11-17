#include "model_functions.h"

double calcLinear(double currentY, double inputU) {
    return (Constants::A * currentY) + (Constants::B * inputU);
}

double calcNonlinear(double currentY, double prevY, double inputU, double prevU) {
    return (Constants::A * currentY) - (Constants::B * prevY * prevY) + (Constants::C * inputU) + Constants::D * sin(prevU);
}