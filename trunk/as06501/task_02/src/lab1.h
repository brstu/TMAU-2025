#pragma once
inline constexpr int N = 10;
inline constexpr double a = 0.97;
inline constexpr double b = 0.015;
inline constexpr double c = 0.45;
inline constexpr double d = 0.08;
inline constexpr double start_value = 18;

double linear(double y, double u);

double nonlinear(double yt, double yt1, double ut, double ut1);
