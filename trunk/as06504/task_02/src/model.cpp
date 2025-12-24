#include "model.h"

double linearStep(double prevY, double prevU, const LinearCfg& cfg) {
    return cfg.alpha * prevY + cfg.beta * prevU;
}

double nonlinearStep(double prevY, double prevY2, double prevU, double prevU2, const NonlinearCfg& cfg) {
    return cfg.alpha * prevY - cfg.beta * prevY2 * prevY2 + cfg.gamma * prevU + cfg.delta * std::sin(prevU2);
}
