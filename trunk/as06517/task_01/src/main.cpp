#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

struct Constants
{
    const double a = 0.8, b = 0.2, c = 0.25, d = 0.1;
};


double linear_model(double y_prev, double u_tau, Constants c) {
    return c.a * y_prev + c.b * u_tau;
}

double nonlinear_model(double y_prev, double y_prev_2, double u_prev, 
                     double u_tau, Constants con) {
    return con.a * y_prev - con.b * pow(y_prev_2, 2) + con.c * u_tau + con.d * sin(u_prev);
}

int main() {
    Constants con;
    double u_prev = 0, u_tau;
    int n;
    double y_prev = 20, y_prev_2 = 20;
    
    std::vector<double> u_vec;
    std::vector<double> linear_result;
    std::vector<double> nonlinear_result;

    std::cout << "=== Temperature Control Object Simulation ===" << std::endl;
    std::cout << "Linear model: y_{τ+1} = a*y_τ + b*u_τ" << std::endl;
    std::cout << "Nonlinear model: y_{τ+1} = a*y_τ - b*y_{τ-1}² + c*u_τ + d*sin(u_{τ-1})" << std::endl;
    std::cout << "Parameters: a=" << con.a << ", b=" << con.b << ", c=" << con.c << ", d=" << con.d << std::endl;
    std::cout << "Initial temperature: " << y_prev << "°C" << std::endl << std::endl;

    std::cout << "Enter number of steps: ";
    std::cin >> n;
    std::cout << "Enter control inputs u(τ) separated by spaces:" << std::endl;
    for (size_t i = 0; i < n; i++) {
        std::cin >> u_tau;
        u_vec.push_back(u_tau);
    }

    double y_prev_linear = y_prev;
    double y_prev_nonlinear = y_prev;

    std::cout << std::endl << "Simulation Results:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << std::setw(5) << "Step" << std::setw(10) << "u(τ)" 
         << std::setw(20) << "Linear Model" << std::setw(20) << "Nonlinear Model" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (size_t i = 0; i < n; i++) {
        u_tau = u_vec[i];

        double linear_temp = linear_model(y_prev_linear, u_tau, con);
        double nonlinear_temp = nonlinear_model(y_prev_nonlinear, y_prev_2,
                                            u_prev, u_tau, con);
        
        linear_result.push_back(linear_temp);
        nonlinear_result.push_back(nonlinear_temp);

        std::cout << std::setw(5) << i + 1 
             << std::setw(10) << std::fixed << std::setprecision(2) << u_tau
             << std::setw(20) << std::fixed << std::setprecision(3) << linear_temp
             << std::setw(20) << std::fixed << std::setprecision(3) << nonlinear_temp 
             << std::endl;

        y_prev_linear = linear_temp;
        y_prev_2 = y_prev_nonlinear;
        y_prev_nonlinear = nonlinear_temp;
        u_prev = u_tau;
    }
    std::cout << std::string(60, '-') << std::endl;
    std::cin.get();

    return 0;
}