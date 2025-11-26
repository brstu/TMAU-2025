#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern const double a;
extern const double b;
extern const double c;
extern const double d;

double linear(double yt, double ut);
double nonlinear(double yt, double yt1, double ut, double ut1);

#endif