#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct ModelConfig {
    static constexpr double a = 0.8;
    static constexpr double b_lin = 0.3;
    static constexpr double b_nonlin = 0.06;
    static constexpr double c = 0.52;
    static constexpr double d = 0.13;

    static constexpr double INITIAL_PREV_U = 0.0;
};

struct IModel {
    virtual ~IModel() = default;
    virtual double step(double y, double u, double prev_u) const = 0;
};

struct LinearModel : IModel {
    double a;
    double b;
    LinearModel(double a_, double b_) : a(a_), b(b_) {}

    double step(double y, double u, double /*prev_u*/) const override {
        return a * y + b * u;
    }
};

struct NonlinearModel : IModel {
    double a;
    double b_nonlin;
    double c;
    double d;
    NonlinearModel(double a_, double b_nonlin_, double c_, double d_)
        : a(a_), b_nonlin(b_nonlin_), c(c_), d(d_) {}

    double step(double y, double u, double prev_u) const override {
        return a * y - b_nonlin * y * y + c * u + d * std::sin(prev_u);
    }
};

int main() {
    int n;
    double y0;
    double u_val;

    std::cout << "Enter number of steps n: ";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "Number of steps must be positive.\n";
        return 1;
    }

    std::cout << "Enter initial temperature y0: ";
    std::cin >> y0;

    std::cout << "Enter constant heating u: ";
    std::cin >> u_val;

    LinearModel linear{ModelConfig::a, ModelConfig::b_lin};
    NonlinearModel nonlinear{ModelConfig::a, ModelConfig::b_nonlin, ModelConfig::c, ModelConfig::d};

    std::vector<const IModel*> models = {&linear, &nonlinear};

    std::vector<std::vector<double>> y(models.size(), std::vector<double>(n + 1, 0.0));
    for (auto& arr : y) arr[0] = y0;

    std::vector<double> u(n + 1, u_val);
    for (int t = 0; t < n; ++t) {
        double prev_u = (t > 0) ? u[t - 1] : ModelConfig::INITIAL_PREV_U;

        for (size_t i = 0; i < models.size(); ++i) {
            y[i][t + 1] = models[i]->step(y[i][t], u[t], prev_u);
        }
    }
    std::cout << "\nSimulation results:\n";
    std::cout << "Step\tLinear\t\tNonlinear\n";
    std::cout << "---------------------------------\n";
    for (int t = 0; t <= n; ++t) {
        std::cout << t << "\t"
                  << std::fixed << std::setprecision(4) << y[0][t]
                  << "\t\t" << y[1][t] << "\n";
    }

    return 0;
}
