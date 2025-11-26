#pragma once
#include <cmath>

class TemperatureModel {
private:
    double a;
    double b;
    double c;
    double d;
    double y_prev;
    double y_prev2;
    double u_prev;
    bool is_nonlinear;

public:
    TemperatureModel(double a_val, double b_val);
    TemperatureModel(double a_val, double b_val, double c_val, double d_val);

    void setInitialConditions(double y0, double y1 = 0, double u0 = 0);
    double calculateNext(double u_current);
    double getCurrentTemperature() const;
};
