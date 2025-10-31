#pragma once
const int STEPS = 10;
const double K1 = 0.99;
const double K2 = 0.01;
const double K3 = 0.5;
const double K4 = 0.1;
const double Y0 = 18.0;
double linModel(double y, double u);
double nonlinEq(double y, double y_prev, double u, double u_prev);