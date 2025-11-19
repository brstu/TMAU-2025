#include <array>
#include <iomanip>
#include <iostream>

#include "func.h"

namespace {
using InputSequence = std::array<double, STEPS>;

InputSequence BuildInputSequence() {
    InputSequence input{};
    for (std::size_t i = 0; i < input.size(); ++i) {
        switch (i % 3) {
            case 0: input[i] = 5.0; break;
            case 1: input[i] = 7.0; break;
            default: input[i] = 0.0; break;
        }
    }
    return input;
}

void SimulateLinear(const InputSequence& input) {
    double y = Y0;
    std::cout << "=== Линейная модель ===\n";
    std::cout << "y0 = " << Y0 << '\n';
    for (std::size_t i = 0; i < input.size(); ++i) {
        y = linear(y, input[i]);
        std::cout << "Шаг " << i + 1 << ": y = " << y << '\n';
    }
}

void SimulateNonlinear(const InputSequence& input) {
    double y_prev = Y0;
    double y = Y0;
    std::cout << "\n=== Нелинейная модель ===\n";
    std::cout << "y0 = " << Y0 << '\n';
    for (std::size_t i = 0; i < input.size(); ++i) {
        const double u_prev = (i == 0) ? input[0] : input[i - 1];
        const double y_new = nonlinear(y, y_prev, input[i], u_prev);
        std::cout << "Шаг " << i + 1 << ": y = " << y_new << '\n';
        y_prev = y;
        y = y_new;
    }
}

}  // namespace

int main() {
    std::cout << std::fixed << std::setprecision(4);
    const auto input = BuildInputSequence();
    SimulateLinear(input);
    SimulateNonlinear(input);
    return 0;
}
