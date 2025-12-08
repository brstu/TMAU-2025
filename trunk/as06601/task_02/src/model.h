#ifndef MODEL_H
#define MODEL_H

// Линейная модель: y[t+1] = a*y[t] + b*u[t]
double linearModel(double a, double b, double y_t, double u_t);

// Нелинейная модель: y[t+1] = a*y[t] - b_nl*y[t]^2 + c*u[t] + d*sin(u_prev)
double nonlinearModel(double a, double b_nl, double c, double d,
                      double y_t, double u_t, double u_prev);

#endif // MODEL_H