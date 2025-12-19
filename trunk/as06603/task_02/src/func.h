#pragma once
#include <cmath>

// Константы модели управления
// Эти значения задаются в func.cpp
extern const int    STEPS;   // количество шагов моделирования
extern const double a;       // коэффициент при y
extern const double b;       // коэффициент при u или y^2
extern const double c;       // коэффициент при управляющем воздействии
extern const double d;       // коэффициент при синусе
extern const double Y0;      // начальное значение температуры

namespace Model {
    // Линейная модель: y_{t+1} = a*y_t + b*u_t
    double linearModel(double y, double u);

    // Нелинейная модель: y_{t+1} = a*y_t - b*y_{t-1}^2 + c*u_t + d*sin(u_{t-1})
    double nonlinearModel(double y, double y_prev, double u, double u_prev);
}
