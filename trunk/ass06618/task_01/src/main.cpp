#include <iostream>
#include <cmath>
#include <iomanip>

// ---------- модели ----------

double linearModel(double state, double input) {
    const double a = 0.8;
    const double b = 0.2;
    return a * state + b * input;
}

double nonlinearModel(double state, double input, double prevInput) {
    const double c1 = 0.7;
    const double c2 = 0.005;
    const double c3 = 0.25;
    const double c4 = 0.1;

    return c1 * state
         - c2 * state * state
         + c3 * input
         + c4 * std::sin(prevInput - 1.0);
}

// ---------- управление ----------

double controlLaw(double linearTemp) {
    if (linearTemp < 18.0) {
        return 1.5;
    }
    if (linearTemp > 28.0) {
        return 0.0;
    }
    return 1.0;
}

// ---------- main ----------

int main() {
    double linearTemp = 20.0;
    double nonlinearTemp = 20.0;

    double u = 1.0;
    double uPrev = u;

    constexpr int iterations = 30;

    std::cout << "Temperature dynamics\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::setw(6)  << "t"
              << std::setw(14) << "Linear"
              << std::setw(14) << "Nonlinear"
              << std::setw(14) << "Control" << '\n';

    for (int step = 0; step < iterations; ++step) {

        std::cout << std::setw(6)  << step
                  << std::setw(14) << std::fixed << std::setprecision(2) << linearTemp
                  << std::setw(14) << nonlinearTemp
                  << std::setw(14) << u << '\n';

        const double nextLinear    = linearModel(linearTemp, u);
        const double nextNonlinear = nonlinearModel(nonlinearTemp, u, uPrev);

        uPrev = u;
        linearTemp = nextLinear;
        nonlinearTemp = nextNonlinear;

        u = controlLaw(linearTemp);
    }

    return 0;
}
