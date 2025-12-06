#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

extern const int n;
extern const double a_lin;
extern const double b_lin;
extern const double a_nonlin;
extern const double b_nonlin;
extern const double c_nonlin;
extern const double d_nonlin;
extern const double Y0;

double linear(double yt, double ut);
double nonlinear(double yt, double yt_1, double ut, double ut_1);

#endif