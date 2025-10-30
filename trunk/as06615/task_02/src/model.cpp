#include "model.h"

double compute_derivative(const std::vector<double>& errors, double dt) {
    if (errors.size() < 2 || dt == 0.0) return 0.0;
    return (errors.back() - *(errors.end() - 2)) / dt;
}
