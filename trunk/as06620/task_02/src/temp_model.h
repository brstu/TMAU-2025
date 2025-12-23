#pragma once
#include <cmath>

class TemperatureModel {
public:
    TemperatureModel(double a_val, double b_val);
    TemperatureModel(double a_val, double b_val, double c_val, double d_val);

    void setInitialConditions(double y0, double y1, double u0);
    double calculateNext(double u_current);
    double getCurrentTemperature() const;

private:
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    double d = 0.0;

    double y_prev = 0.0;
    double y_prev2 = 0.0;
    double u_prev = 0.0;

    bool is_nonlinear = false;
};
