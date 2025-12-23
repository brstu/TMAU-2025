#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

extern const double a;
extern const double b_lin; 
extern const double b_non;  
extern const double c;
extern const double d;

double linear(double yt, double ut);
double nonlinear(double yt, double yt1, double ut, double ut1);

void simulateLinear(double a, double b_lin_param,
    const std::vector<double>& u,
    std::vector<double>& y_out);

void simulateNonlinear(double a, double b_non, double c, double d,
    const std::vector<double>& u,
    std::vector<double>& y_out);

#endif
