#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>



void simulateLinear(double a, double b_lin,
    const std::vector<double>& u,
    std::vector<double>& y_out)
{
    const std::size_t n = u.size();
    for (std::size_t t = 0; t + 1 < n; ++t) {
        y_out[t + 1] = a * y_out[t] + b_lin * u[t];
    }
}

void simulateNonlinear(double a, double b_non, double c, double d,
    const std::vector<double>& u,
    std::vector<double>& y_out)
{
    const std::size_t n = u.size();
    if (n == 0) return;


    if (n > 1) {
        y_out[1] = a * y_out[0]
            - b_non * (y_out[0] * y_out[0])
            + c * u[0]
            + d * std::sin(u[0]);
    }

    // for t >= 1 compute normally y[t+1]
    for (std::size_t t = 1; t + 1 < n; ++t) {
        double y_t = y_out[t];
        double y_tm1 = y_out[t - 1];
        double u_tm1 = u[t - 1];
        y_out[t + 1] = a * y_t
            - b_non * (y_tm1 * y_tm1)
            + c * u[t]
            + d * std::sin(u_tm1);
    }
}

int main()
{
    const std::size_t n = 20; // number of discrete time steps

    // --- Input signal u(t) ---
    std::vector<double> u(n, 0.0);
    for (std::size_t i = 0; i < n; ++i) {
        if (i >= 5) {
            u[i] = 10.0; // step control after the 5th step
        }
    }

    // --- Output vectors ---
    std::vector<double> y_linear(n, 0.0);
    std::vector<double> y_nonlinear(n, 0.0);

    // --- Initial conditions ---
    const double Y0 = 20.0; // начальная температура
    y_linear[0] = Y0;
    y_nonlinear[0] = Y0;

    // --- Model parameters ---
    const double a = 0.92;
    const double b_lin = 0.08;
    const double b_non = 0.005;
    const double c = 0.07;
    const double d = 0.04;

    // Run simulations
    simulateLinear(a, b_lin, u, y_linear);
    simulateNonlinear(a, b_non, c, d, u, y_nonlinear);

    // --- Print results side-by-side ---
    std::cout << std::fixed << std::setprecision(4);
    std::cout << " t  \tu(t)    \tlinear y\tnonlinear y" << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
    for (std::size_t t = 0; t < n; ++t) {
        std::cout << std::setw(2) << t << "  \t"
                  << std::setw(7) << u[t] << "  \t"
                  << std::setw(9) << y_linear[t] << "  \t"
                  << std::setw(11) << y_nonlinear[t] << "\n";
    }

    return 0;
}
