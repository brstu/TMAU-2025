#include "func.h"

double linearModel(double y, double u) {
    return kA * y + kB * u;
}

double nonlinearModel(double y, double yPrev, double u, double uPrev) {
    return kA * y + kB * pow(yPrev, 2) + kC * u + kD * sin(uPrev);
}
