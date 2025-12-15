#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <iomanip>

struct State {
    double linear;
    double nonlinear;
    double control;
};

struct Params {
    double a, b;
    double p1, p2, p3, p4;
};

using Model = std::function<State(const State&, double)>;

// управление как политика
double controlPolicy(double temp) {
    return (temp < 18.0) ? 1.5 :
           (temp > 28.0) ? 0.0 : 1.0;
}

// модель как трансформация состояния
Model buildModel(const Params& p) {
    return [p](const State& prev, double prevControl) {
        State next;

        next.linear =
            std::fma(p.a, prev.linear, p.b * prev.control);

        next.nonlinear =
            p.p1 * prev.nonlinear
            - p.p2 * prev.nonlinear * prev.nonlinear
            + p.p3 * prev.control
            + p.p4 * std::sin(prevControl - 1.0);

        next.control = controlPolicy(next.linear);
        return next;
    };
}

// симуляция без "классического цикла"
std::vector<State> simulate(
    State initial,
    Model model,
    std::size_t steps)
{
    std::vector<State> trajectory;
    trajectory.reserve(steps);

    double prevU = initial.control;
    State current = initial;

    while (trajectory.size() < steps) {
        trajectory.push_back(current);
        State next = model(current, prevU);
        prevU = current.control;
        current = next;
    }

    return trajectory;
}

void render(const std::vector<State>& data) {
    std::cout << " t     linear     nonlinear    control\n";
    std::cout << "--------------------------------------\n";

    int t = 0;
    for (const auto& s : data) {
        std::cout << std::setw(2) << t++
                  << std::setw(12) << std::fixed << std::setprecision(2) << s.linear
                  << std::setw(14) << s.nonlinear
                  << std::setw(11) << s.control << '\n';
    }
}

int main() {
    Params params{0.8, 0.2, 0.7, 0.005, 0.25, 0.1};

    State start{20.0, 20.0, 1.0};

    auto model = buildModel(params);
    auto result = simulate(start, model, 30);

    render(result);
}
