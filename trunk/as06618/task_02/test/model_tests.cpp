#include <gtest/gtest.h>
#include "model.h"
#include <cmath>

static Params P{0.92, 0.08, 0.07, 0.04};

TEST(LinearStep, BasicFormula) {
    EXPECT_DOUBLE_EQ(linear_step(10.0, 5.0, P), 0.92 * 10.0 + 0.08 * 5.0);
}

TEST(LinearStep, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_step(7.0, 0.0, P), 0.92 * 7.0);
}

TEST(NonlinearStep, FullFormula) {
    double res = nonlinear_step(5.0, 3.0, 2.0, 1.0, P);
    double expected =
        0.92 * 5.0
        - 0.08 * 3.0 * 3.0
        + 0.07 * 2.0
        + 0.04 * std::sin(1.0);
    EXPECT_DOUBLE_EQ(res, expected);
}

TEST(LinearSimulation, SizePreserved) {
    std::vector<double> u(10, 1.0);
    auto y = simulate_linear(0.0, u, P);
    EXPECT_EQ(y.size(), u.size());
}

TEST(NonlinearSimulation, StartsWithInitialValue) {
    std::vector<double> u(5, 0.0);
    auto y = simulate_nonlinear(20.0, u, P);
    EXPECT_DOUBLE_EQ(y[0], 20.0);
}

TEST(Models, ProduceDifferentResults) {
    std::vector<double> u(5, 5.0);
    auto y1 = simulate_linear(10.0, u, P);
    auto y2 = simulate_nonlinear(10.0, u, P);
    EXPECT_NE(y1[2], y2[2]);
}
