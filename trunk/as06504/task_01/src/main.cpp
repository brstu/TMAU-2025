#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct LinearCfg {
    double alpha;
    double beta;
};

struct NonlinearCfg {
    double alpha;
    double beta;
    double gamma;
    double delta;
};

double linearStep(double prevY, double prevU, const LinearCfg& cfg) {
    return cfg.alpha * prevY + cfg.beta * prevU;
}

double nonlinearStep(double prevY, double prevY2, double prevU, double prevU2, const NonlinearCfg& cfg) {
    return cfg.alpha * prevY - cfg.beta * prevY2 * prevY2 + cfg.gamma * prevU + cfg.delta * std::sin(prevU2);
}

void simulateSystem(int nSteps) {
    LinearCfg linCfg{0.65, 0.25};
    NonlinearCfg nonlinCfg{0.65, 0.25, 0.05, 0.20};

    std::vector<double> control(nSteps, 1.0);
    std::vector<double> yLinear(nSteps, 0.0);
    std::vector<double> yNonlinear(nSteps, 0.0);

    for (int k = 1; k < nSteps; ++k) {
        yLinear[k] = linearStep(yLinear[k - 1], control[k - 1], linCfg);

        if (k == 1) {
            yNonlinear[k] = linearStep(yNonlinear[k - 1], control[k - 1], {nonlinCfg.alpha, nonlinCfg.gamma});
        } else {
            yNonlinear[k] = nonlinearStep(yNonlinear[k - 1], yNonlinear[k - 2], control[k - 1], control[k - 2], nonlinCfg);
        }
    }

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n=== Temperature Simulation ===\n";
    std::cout << "Step | Linear    | Nonlinear\n";
    std::cout << "-------------------------------\n";

    for (int k = 0; k < nSteps; ++k) {
        std::cout << std::setw(3) << k << " | "
                  << std::setw(8) << yLinear[k] << " | "
                  << std::setw(10) << yNonlinear[k] << "\n";
    }
}

int main() {
    int stepsCount = 20;
    simulateSystem(stepsCount);
    return 0;
}
