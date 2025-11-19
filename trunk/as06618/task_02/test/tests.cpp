#include <cmath>
#include <iostream>

#include "func.h"

namespace {
bool AlmostEqual(double lhs, double rhs, double eps = 1e-9) {
    return std::fabs(lhs - rhs) <= eps;
}

bool ExpectEqual(double lhs, double rhs, const char* description) {
    if (AlmostEqual(lhs, rhs)) {
        return true;
    }
    std::cerr << "Тест не пройден: " << description << "\n"
              << "  Ожидалось: " << rhs << "\n"
              << "  Получено : " << lhs << "\n";
    return false;
}
}  // namespace

int main() {
    bool ok = true;
    ok &= ExpectEqual(linear(0.0, 0.0), 0.0, "Linear zero input");
    ok &= ExpectEqual(linear(18.0, 0.0), a * 18.0, "Linear zero control");
    ok &= ExpectEqual(linear(0.0, 5.0), b * 5.0, "Linear zero state");
    ok &= ExpectEqual(linear(18.0, 5.0), a * 18.0 + b * 5.0, "Linear generic");

    ok &= ExpectEqual(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0, "Nonlinear zero input");
    ok &= ExpectEqual(nonlinear(18.0, 18.0, 0.0, 0.0),
                      a * 18.0 - b * std::pow(18.0, 2),
                      "Nonlinear zero control");
    ok &= ExpectEqual(nonlinear(0.0, 0.0, 5.0, 5.0),
                      c * 5.0 + d * std::sin(5.0),
                      "Nonlinear zero state");
    ok &= ExpectEqual(nonlinear(18.0, 18.0, 5.0, 5.0),
                      a * 18.0 - b * std::pow(18.0, 2) + c * 5.0 + d * std::sin(5.0),
                      "Nonlinear generic");

    if (!ok) {
        return 1;
    }

    std::cout << "Все тесты пройдены" << std::endl;
    return 0;
}
