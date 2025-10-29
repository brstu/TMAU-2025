#pragma once
const int N = 10;
const double a = 0.97;
const double b = 0.015;
const double c = 0.45;
const double d = 0.08;
//double start_value = 18;

double linear(double y, double u);

double nonlinear(double yt, double yt1, double ut, double ut1);
