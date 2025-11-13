#pragma once

// Model constants
inline constexpr int n = 10;        
inline constexpr double a = 0.98;
inline constexpr double b = 0.02;
inline constexpr double c = 0.4;
inline constexpr double d = 0.15;
inline constexpr double Y0 = 20;
inline constexpr double u = 8.0;

// Function prototypes
double linear(double y, double u_val);
double nonlinear(double yt, double yt1, double ut, double ut1);
