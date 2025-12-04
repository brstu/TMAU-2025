// temperature_model.h
#ifndef TEMPERATURE_MODEL_H
#define TEMPERATURE_MODEL_H

#include <vector>

struct LinearParams {
    double alpha;
    double beta;
};

struct NonlinearParams {
    double alpha;
    double beta;
    double gamma;
    double delta;
};

double simulate_linear(double temp, double heat, const LinearParams& p);

double simulate_nonlinear(double temp_now, double temp_prev, double heat_now, double heat_prev, const NonlinearParams& p);

void run_simulation(int steps, const LinearParams& lin, const NonlinearParams& nonlin);

#endif // TEMPERATURE_MODEL_H