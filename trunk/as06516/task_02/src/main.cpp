#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "functions.h"  

void simulateLinear(double a_param, double b_lin_param,
    const std::vector<double>& u,
    std::vector<double>& y_out)
{
    const std::size_t n = u.size();
    for (std::size_t t = 0; t + 1 < n; ++t) {
        y_out[t + 1] = a_param * y_out[t] + b_lin_param * u[t];
    }
}

void simulateNonlinear(double a_param, double b_non_param, double c_param, double d_param,
    const std::vector<double>& u,
    std::vector<double>& y_out)
{
    const std::size_t n = u.size();
    if (n == 0) return;
    
    if (n > 1) {
        double y_tm1 = y_out[0];
        double u_tm1 = u[0];
        y_out[1] = a_param * y_out[0] - b_non_param * (y_tm1 * y_tm1) + c_param * u[0] + d_param * std::sin(u_tm1);
    }
    
    for (std::size_t t = 1; t + 1 < n; ++t) {
        double y_t = y_out[t];
        double y_tm1 = y_out[t - 1];
        double u_tm1 = u[t - 1];
        y_out[t + 1] = a_param * y_t - b_non_param * (y_tm1 * y_tm1) + c_param * u[t] + d_param * std::sin(u_tm1);
    }
}

#ifdef STANDALONE
int main()
{
    const std::size_t n = 20;
    std::vector<double> u(n, 0.0);
    
    for (std::size_t i = 0; i < n; ++i) {
        if (i >= 5) {
            u[i] = 10.0;
        }
    }
    
    std::vector<double> y_linear(n, 0.0);
    std::vector<double> y_nonlinear(n, 0.0);
    
    const double Y0 = 20.0;
    y_linear[0] = Y0;
    y_nonlinear[0] = Y0;
    
    const double a_val = 0.92;        
    const double b_lin_val = 0.08;    
    const double b_non_val = 0.005;   
    const double c_val = 0.07;        
    const double d_val = 0.04;        
    
    simulateLinear(a_val, b_lin_val, u, y_linear);
    simulateNonlinear(a_val, b_non_val, c_val, d_val, u, y_nonlinear);
    
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
#endif
