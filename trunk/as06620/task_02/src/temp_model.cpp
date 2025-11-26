#include "temp_model.h"

TemperatureModel::TemperatureModel(double a_val, double b_val)
    : a(a_val), b(b_val) {}

TemperatureModel::TemperatureModel(double a_val, double b_val, double c_val, double d_val)
    : a(a_val), b(b_val), c(c_val), d(d_val), is_nonlinear(true) {}

void TemperatureModel::setInitialConditions(double y0, double y1, double u0) {
    y_prev = y0;
    y_prev2 = y1;
    u_prev = u0;
}

double TemperatureModel::calculateNext(double u_current) {
    double y_next;

    if (is_nonlinear) {
        y_next = a * y_prev - b * y_prev2 * y_prev2 + c * u_current + d * sin(u_prev);
    } else {
        y_next = a * y_prev + b * u_current;
    }

    y_prev2 = y_prev;
    y_prev = y_next;
    u_prev = u_current;

    return y_next;
}

double TemperatureModel::getCurrentTemperature() const {
    return y_prev;
}
