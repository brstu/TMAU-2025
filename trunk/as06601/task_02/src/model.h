#ifndef MODEL_H
#define MODEL_H

#include <cmath>

// внутренняя безопасная функция — реальная логика
double nonlinearModelImpl(double a, double b, double c, double d,
                          double y_t, double y_prev,
                          double u_t, double u_prev);

// внешняя обёртка — только для совместимости с main
inline double nonlinearModel(double a, double b, double c, double d,
                             double y_t, double y_prev,
                             double u_t, double u_prev)
{
    return nonlinearModelImpl(a, b, c, d, y_t, y_prev, u_t, u_prev);
}

// линейная модель — тоже безопасная
double linearModel(double a, double b, double y_t, double u_t);

#endif
