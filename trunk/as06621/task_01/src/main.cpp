#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

// Конфигурационные параметры модели
struct Config {
    static constexpr double A = 0.9;
    static constexpr double B_lin = 0.2;
    static constexpr double B_nonlin = 0.01;
    static constexpr double C = 0.15;
    static constexpr double D = 0.05;

    static constexpr double ZERO_PREV_INPUT = 0.0; // prev_u при t=0
};

// Линейная модель
class Linear {
public:
    Linear(double a, double b) : a_(a), b_(b) {}
    double next(double y, double u) const {
        return a_ * y + b_ * u;
    }
private:
    double a_;
    double b_;
};

// Нелинейная модель
class Nonlinear {
public:
    Nonlinear(double a, double b, double c, double d)
        : a_(a), b_(b), c_(c), d_(d) {}

    double next(double y, double u, double prev_u) const {
        return a_ * y - b_ * y * y + c_ * u + d_ * std::sin(prev_u);
    }
private:
    double a_;
    double b_;
    double c_;
    double d_;
};

int main() {
    int steps;
    double y_init;
    double u_const;

    std::cout << "Введите количество шагов моделирования: ";
    std::cin >> steps;
    if (steps <= 0) {
        std::cerr << "Ошибка: число шагов должно быть положительным.\n";
        return 1;
    }

    std::cout << "Введите начальную температуру y0: ";
    std::cin >> y_init;

    std::cout << "Введите постоянное нагревание u: ";
    std::cin >> u_const;

    Linear lin(Config::A, Config::B_lin);
    Nonlinear nonlin(Config::A, Config::B_nonlin, Config::C, Config::D);

    std::vector<double> y_l(steps + 1, 0.0);
    std::vector<double> y_nl(steps + 1, 0.0);
    // Используем u_const напрямую, вместо вектора u, поскольку в данной реализации предполагается постоянный вход (нагревание) на протяжении всей симуляции.
    // Если потребуется моделировать переменный вход, следует использовать вектор u.

    y_l[0] = y_init;
    y_nl[0] = y_init;

    for (int t = 0; t < steps; ++t) {
        y_l[t + 1] = lin.next(y_l[t], u_const);
        double prev_u = (t > 0 ? u_const : Config::ZERO_PREV_INPUT);
        y_nl[t + 1] = nonlin.next(y_nl[t], u_const, prev_u);
    }

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t\tЛинейная\tНелинейная\n";
    std::cout << "---------------------------------\n";

    for (int t = 0; t <= steps; ++t) {
        std::cout << t << "\t"
                  << std::fixed << std::setprecision(4) << y_l[t] << "\t\t"
                  << y_nl[t] << "\n";
    }

    return 0;
}
