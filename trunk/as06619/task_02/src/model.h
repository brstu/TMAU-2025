#ifndef MODEL_H
#define MODEL_H

double compute_linear_model(double y_prev, double u, double a, double b);
double compute_nonlinear_model(double y_curr, double y_prev, double u_curr, double u_prev, double a, double b, double c, double d);

#endif
