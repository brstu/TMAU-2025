#pragma once
#include <array>

// Константы из вашей лабораторной работы
const int N = 15;
const double A = 0.9;
const double B = 0.01;
const double C_val = 0.4;
const double D_val = 0.1;
const double Y_start = 20;

extern const std::array<double, N> U;  // Массив управляющих воздействий

// Объявления функций
double linearModel(double y, double u);
double nonlinearModel(double y_curr, double y_prev, double u_curr, double u_prev);
