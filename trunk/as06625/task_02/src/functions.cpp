#include "functions.h"
#include <cmath>
#include <stdexcept>

namespace system_model {

// параметры системы
const double a     = 0.92;
const double b_lin = 0.08;
const double b_non = 0.005;
const double c     = 0.07;
const double d     = 0.04;

double linear(double state, double input) {
    return std::fma(a, state, b_lin * input);
}

double nonlinear(double y_t, double y_tm1, double u_t, double u_tm1) {
    const double decay = a * y_t;
    const double quad  = b_non * y_tm1 * y_tm1;
    const double drive = c * u_t;
    const double wave  = d * std::sin(u_tm1);
    return decay - quad + drive + wave;
}

void run_linear(const std::vector<double>& u, std::vector<double>& y) {
    if (u.size() != y.size() || y.empty())
        throw std::invalid_argument("Dimension mismatch");

    for (std::size_t k = 1; k < u.size(); ++k) {
        y[k] = linear(y[k - 1], u[k - 1]);
    }
}

void run_nonlinear(const std::vector<double>& u, std::vector<double>& y) {
    if (u.size() != y.size() || y.empty())
        throw std::invalid_argument("Dimension mismatch");

    if (u.size() > 1) {
        y[1] = nonlinear(y[0], y[0], u[0], u[0]);
    }

    for (std::size_t k = 2; k < u.size(); ++k) {
        y[k] = nonlinear(y[k - 1], y[k - 2], u[k - 1], u[k - 2]);
    }
}

} // namespace system_model
