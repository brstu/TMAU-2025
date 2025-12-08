#ifndef MODEL_H
#define MODEL_H

struct NonlinearParams {
    double a;
    double b_nl;
    double c;
    double d;
};

double linearModel(double a, double b, double y_t, double u_t);
double nonlinearModel(const NonlinearParams& params, double y_t, double u_t, double u_prev);

#endif // MODEL_H