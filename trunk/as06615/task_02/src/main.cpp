#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>
#include "model.h"

int main() {
    const double dt = 0.1;
    const double x_ref = 10.0;
    const double kp = 2.0;
    const double d = 0.5;
    const double c = 0.0001;
    const double s = 0.01;
    const int steps = 100;

    std::vector<double> x1_lin = {0.0};
    std::vector<double> x2_lin = {0.0};
    std::vector<double> u_lin;
    std::vector<double> err_lin = {x_ref};

    std::vector<double> x1_non = {0.0};
    std::vector<double> x2_non = {0.0};
    std::vector<double> u_non = {0.0};
    std::vector<double> err_non = {x_ref};

    std::ofstream out("trajectory.csv");
    if (!out.is_open()) {
        std::cerr << "Error: could not open file trajectory.csv\n";
        return 1;
    }

    out << "t,x1_linear,x2_linear,u_linear,x1_nonlinear,x2_nonlinear,u_nonlinear\n";

    for (int t = 0; t < steps; ++t) {
        // Линейная модель
        double e_lin = x_ref - x1_lin.back();
        err_lin.push_back(e_lin);
        double de_lin = compute_derivative(err_lin, dt);
        double u_t_lin = kp * e_lin + d * de_lin;
        u_lin.push_back(u_t_lin);

        double x1_next_lin = x1_lin.back() + dt * x2_lin.back();
        double x2_next_lin = x2_lin.back() + dt * u_t_lin;
        x1_lin.push_back(x1_next_lin);
        x2_lin.push_back(x2_next_lin);

        // Нелинейная модель
        double e_non = x_ref - x1_non.back();
        err_non.push_back(e_non);
        double de_non = compute_derivative(err_non, dt);
        double u_prev = u_non.back();
        double u_t_non = kp * e_non + d * de_non + c * std::pow(u_prev, 2) + s * std::sin(u_prev);
        u_non.push_back(u_t_non);

        double x1_next_non = x1_non.back() + dt * x2_non.back();
        double x2_next_non = x2_non.back() + dt * u_t_non;
        x1_non.push_back(x1_next_non);
        x2_non.push_back(x2_next_non);

        out << t * dt << ","
            << x1_next_lin << "," << x2_next_lin << "," << u_t_lin << ","
            << x1_next_non << "," << x2_next_non << "," << u_t_non << "\n";
    }

    out.close();
    std::cout << "Simulation complete, trajectory.csv\n";
    return 0;
}