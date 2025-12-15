#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

struct Coeffs {
    double a{};
    double b{};
    double c{};
    double d{};
};

// u(t): управляющее воздействие (можно заменить на своё)
double inputSignal(std::size_t t) {
    // пример: ступенька после 5-го шага
    return (t >= 5) ? 10.0 : 0.0;
}

double nextLinear(double y_t, double u_t, const Coeffs& k) {
    return k.a * y_t + k.b * u_t;
}

// y_{t+1} = a*y_t - b*(y_{t-1})^2 + c*u_t + d*sin(u_{t-1})
double nextNonlinear(double y_t, double y_tm1, double u_t, double u_tm1, const Coeffs& k) {
    return k.a * y_t - k.b * (y_tm1 * y_tm1) + k.c * u_t + k.d * std::sin(u_tm1);
}

int main(int argc, char** argv) {
    // параметры модели (можешь поменять под свой вариант)
    const Coeffs k{0.92, 0.08, 0.07, 0.04};  // a,b,c,d
    const std::size_t steps = 20;
    const double y0 = 20.0;

    // формируем u(t)
    std::vector<double> u(steps, 0.0);
    for (std::size_t t = 0; t < steps; ++t) {
        u[t] = inputSignal(t);
    }

    // траектории
    std::vector<double> yLin(steps, 0.0);
    std::vector<double> yNon(steps, 0.0);

    yLin[0] = y0;
    yNon[0] = y0;

    // линейная модель (t=0..steps-2)
    for (std::size_t t = 0; t + 1 < steps; ++t) {
        yLin[t + 1] = nextLinear(yLin[t], u[t], k);
    }

    // нелинейная модель:
    // договоримся: y_{-1} = y_0, u_{-1} = u_0 для первого шага
    if (steps > 1) {
        yNon[1] = nextNonlinear(yNon[0], yNon[0], u[0], u[0], k);
    }
    for (std::size_t t = 1; t + 1 < steps; ++t) {
        yNon[t + 1] = nextNonlinear(yNon[t], yNon[t - 1], u[t], u[t - 1], k);
    }

    // вывод
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "t\tu(t)\tlinear\t\tnonlinear\n";
    std::cout << "---------------------------------------------\n";
    for (std::size_t t = 0; t < steps; ++t) {
        std::cout << t << '\t'
                  << u[t] << '\t'
                  << yLin[t] << "\t\t"
                  << yNon[t] << '\n';
    }

    return 0;
}