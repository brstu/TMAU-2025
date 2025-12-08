#include "model.h"
#include <cmath>

// безопасная реализация линейной модели
double linearModel(double a, double b, double y_t, double u_t) {
    return a * y_t + b * u_t;
}

// реальная логика нелинейной модели
double nonlinearModelImpl(double a, double b, double c, double d,
                          double y_t, double y_prev,
                          double u_t, double u_prev)
{
    return a * y_t
         - b * y_prev * y_prev
         + c * u_t
         + d * sin(u_prev);
}
