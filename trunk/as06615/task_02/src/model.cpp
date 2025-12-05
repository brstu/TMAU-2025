#include "model.h"
#include <cmath>
#include <limits>

double compute_derivative(const std::vector<double>& errors, double dt) {
    if (errors.size() < 2) return 0.0;
    if (dt < 0.0) return 0.0;
    if (std::abs(dt) < std::numeric_limits<double>::epsilon()) return 0.0;
    return (errors.back() - *(errors.end() - 2)) / dt;
}