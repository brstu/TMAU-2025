#pragma once
#include <cmath>

struct Lin {
    double a;
    double b;
};

struct Nonlin {
    double a;
    double b;
    double c;
    double d;
};

double step_lin(double y, double u, const Lin& p);
double step_nonlin(double y1, double y2, double u1, double u2, const Nonlin& p);
void simulate(int N);
