#ifndef MODEL_H
#define MODEL_H

#include <cmath>

struct ParamsLin {
    const double a;
    const double b;
};

struct ParamsNonlin {
    const double a;
    const double b;
    const double c;
    const double d;
};

double model_linear(double y, double u, const ParamsLin& p);
double model_nonlinear(double y, double y_prev, double u, double u_prev, const ParamsNonlin& p);

#endif
