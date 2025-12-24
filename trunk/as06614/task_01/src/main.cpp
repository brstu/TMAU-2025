#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Конфигурационные параметры модели
struct Config {
    static constexpr double A = 0.8;
    static constexpr double B_LIN = 0.2;
    static constexpr double B_NONLIN = 0.1;
    static constexpr double C = 0.3;
    static constexpr double D = 0.1;
    static constexpr double Y_INIT = 20.0;
    static constexpr double Y_PREV = 18.0;
};

// Линейная модель
class LinearModel {
public:
    LinearModel(double a, double b) : a_(a), b_(b) {}
    
    std::vector<double> simulate(const std::vector<double>& u, double y0) const {
        std::vector<double> y(u.size() + 1);
        y[0] = y0;
        for (size_t t = 0; t < u.size(); ++t) {
            y[t + 1] = a_ * y[t] + b_ * u[t];
        }
        return y;
    }
    
private:
    double a_;
    double b_;
};

// Нелинейная модель
class NonlinearModel {
public:
    NonlinearModel(double a, double b, double c, double d) 
        : a_(a), b_(b), c_(c), d_(d) {}
    
    std::vector<double> simulate(const std::vector<double>& u, double y0, double y_prev) const {
        std::vector<double> y(u.size() + 1);
        y[0] = y0;
        
        if (!u.empty()) {
            // Для первого шага: y[1] = a*y[0] - b*y_prev^2 + c*u[0] + d*sin(u[0])
            y[1] = a_ * y[0] - b_ * std::pow(y_prev, 2) + c_ * u[0] + d_ * std::sin(u[0]);
        }
        
        for (size_t t = 1; t < u.size(); ++t) {
            // Для остальных шагов: y[t+1] = a*y[t] - b*y[t-1]^2 + c*u[t] + d*sin(u[t-1])
            y[t + 1] = a_ * y[t] - b_ * std::pow(y[t - 1], 2) + c_ * u[t] + d_ * std::sin(u[t - 1]);
        }
        
        return y;
    }
    
private:
    double a_;
    double b_;
    double c_;
    double d_;
};

int main() {
    LinearModel linear(Config::A, Config::B_LIN);
    NonlinearModel nonlinear(Config::A, Config::B_NONLIN, Config::C, Config::D);
    
    std::vector<double> u = {10.0, 12.0, 15.0, 14.0, 13.0};
    
    std::cout << "Параметры модели:\n";
    std::cout << "a = " << Config::A << "\n";
    std::cout << "b_lin = " << Config::B_LIN << "\n";
    std::cout << "b_nonlin = " << Config::B_NONLIN << "\n";
    std::cout << "c = " << Config::C << "\n";
    std::cout << "d = " << Config::D << "\n";
    std::cout << "y0 = " << Config::Y_INIT << "\n";
    std::cout << "y_{-1} = " << Config::Y_PREV << "\n";
    std::cout << "Входные воздействия u: ";
    for (double val : u) {
        std::cout << val << " ";
    }
    std::cout << "\n\n";
    
    std::vector<double> y_linear = linear.simulate(u, Config::Y_INIT);
    std::vector<double> y_nonlinear = nonlinear.simulate(u, Config::Y_INIT, Config::Y_PREV);
    
    std::cout << "ЛИНЕЙНАЯ МОДЕЛЬ\n";
    std::cout << "Шаг\tТемпература y(τ)\n";
    std::cout << "-------------------\n";
    for (size_t t = 0; t < y_linear.size(); ++t) {
        std::cout << t << "\t" << std::fixed << std::setprecision(4) << y_linear[t] << "\n";
    }
    
    std::cout << "\nНЕЛИНЕЙНАЯ МОДЕЛЬ\n";
    std::cout << "Шаг\tТемпература y(τ)\n";
    std::cout << "-------------------\n";
    for (size_t t = 0; t < y_nonlinear.size(); ++t) {
        std::cout << t << "\t" << std::fixed << std::setprecision(4) << y_nonlinear[t] << "\n";
    }
    
    std::cout << "\nСРАВНЕНИЕ МОДЕЛЕЙ\n";
    std::cout << "Шаг\tЛинейная\tНелинейная\n";
    std::cout << "---------------------------------\n";
    for (size_t t = 0; t < y_linear.size(); ++t) {
        std::cout << t << "\t" 
                  << std::fixed << std::setprecision(4) << y_linear[t] << "\t\t"
                  << y_nonlinear[t] << "\n";
    }
    
    return 0;
}