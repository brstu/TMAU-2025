#pragma once
constexpr int n = 10;        // time steps
constexpr double a = 0.99;
constexpr double b = 0.01;
constexpr double c = 0.5;
constexpr double d = 0.1;
constexpr double Y0 = 18;
double linear(double yt, double ut);
double nonlinear(double yt, double yt_1, double ut, double ut_1);