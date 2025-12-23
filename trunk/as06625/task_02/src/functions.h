#pragma once
#include <vector>

namespace system_model {

// параметры (API сохранён для тестов)
extern const double a;
extern const double b_lin;
extern const double b_non;
extern const double c;
extern const double d;

// элементарные шаги
double linear(double state, double input);
double nonlinear(double y_t, double y_tm1, double u_t, double u_tm1);

// моделирование траекторий
void run_linear(const std::vector<double>& u, std::vector<double>& y);
void run_nonlinear(const std::vector<double>& u, std::vector<double>& y);

} // namespace system_model
