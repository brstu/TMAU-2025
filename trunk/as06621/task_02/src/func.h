#pragma once
#include <cmath>

constexpr double a = 0.9;
constexpr double b = 0.01;
constexpr double c = 0.15;
constexpr double d = 0.05;

constexpr double ZERO_PREV_INPUT = 0.0;

// тесты ожидают 2 аргумента для linear и 4 аргумента для nonlinear
double linear(double yt, double ut);
double nonlinear(double yt, double yt_1, double ut, double ut_1);
