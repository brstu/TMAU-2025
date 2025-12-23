#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<double> linear_model(double a, double b, const std::vector<double>& u, double y0) {
    std::vector<double> y(u.size() + 1);
    y[0] = y0;
    for (std::size_t t = 0; t < u.size(); ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }
    return y;
}

std::vector<double> nonlinear_model(double a, double b, double c, double d,
                                    const std::vector<double>& u,
                                    double y0, double y_minus1) {
    std::vector<double> y(u.size() + 1);
    y[0] = y0;
    if (!u.empty()) {
        y[1] = a * y[0] - b * std::pow(y_minus1, 2) + c * u[0] + d * std::sin(u[0]);
    }
    for (std::size_t t = 1; t < u.size(); ++t) {
        y[t + 1] = a * y[t] - b * std::pow(y[t - 1], 2) + c * u[t] + d * std::sin(u[t - 1]);
    }
    return y;
}

int main() {
    const double a = 0.8;
    const double b = 0.2;
    const double c = 0.3;
    const double d = 0.1;
    const double y0 = 20.0;
    const double y_minus1 = 18.0;
    const std::vector<double> u = {10.0, 12.0, 15.0, 14.0, 13.0};
    
    std::cout << "Параметры модели:\n";
    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n";
    std::cout << "d = " << d << "\n";
    std::cout << "y0 = " << y0 << "\n";
    std::cout << "y_{-1} = " << y_minus1 << "\n";
    std::cout << "Входные воздействия u: ";
    for (double val : u) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";
    
    std::cout << "ЛИНЕЙНАЯ МОДЕЛЬ\n";
    std::cout << "Шаг\tТемпература y(τ)\n";
    std::vector<double> y_linear = linear_model(a, b, u, y0);
    for (std::size_t t = 0; t < y_linear.size(); ++t) {
        std::cout << t << "\t" << std::fixed << std::setprecision(4) << y_linear[t] << "\n";
    }
    
    std::cout << "\nНЕЛИНЕЙНАЯ МОДЕЛЬ\n";
    std::cout << "Шаг\tТемпература y(τ)\n";
    std::vector<double> y_nonlinear = nonlinear_model(a, b, c, d, u, y0, y_minus1);
    for (std::size_t t = 0; t < y_nonlinear.size(); ++t) {
        std::cout << t << "\t" << std::fixed << std::setprecision(4) << y_nonlinear[t] << "\n";
    }
    
    return 0;
}