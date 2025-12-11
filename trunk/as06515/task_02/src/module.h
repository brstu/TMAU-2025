#ifndef MODULE_H
#define MODULE_H

#include <vector>

const int MAX_STEPS = 101;

void compute_linear(int N, double a, double b, const std::vector<double>& u, std::vector<double>& y_lin);
void compute_nonlinear(int N, double a, double b, double c, double d, const std::vector<double>& u, std::vector<double>& y_nl);

#endif // MODULE_H

