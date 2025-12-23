#ifndef MODEL_H
#define MODEL_H

#include <vector>

double nonlinearModel(double a, double b_nl, double c, double d,
                      double y_t, double u_t, double u_prev);

double linearModel(double a, double b, double y_t, double u_t);

std::vector<double> simulateLinear(int n, double a, double b, double y0, double u0);

std::vector<double> simulateNonlinear(int n, double a, double b_nl, double c, double d, double y0, double u0);

#endif