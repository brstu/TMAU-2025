#pragma once
constexpr int n = 10;        
constexpr double a = 0.98;
constexpr double b = 0.02;
constexpr double c = 0.4;
constexpr double d = 0.15;
constexpr double Y0 = 20;
constexpr double u = 8.0;
double linear(double y, double u_val);
double nonlinear(double yt, double yt1, double ut, double ut1);
