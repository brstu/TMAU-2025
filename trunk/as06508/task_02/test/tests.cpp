#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

TEST(LinearStepTest, BasicBehavior) {
    ModelParams p;
    double result = linearStep(10.0, 5.0, p);
    EXPECT_NEAR(result, p.a * 10.0 + p.b * 5.0, 1e-9);
}

TEST(NonlinearStepTest, IncludesSinAndSquareTerms) {
    ModelParams p;
    double result = nonlinearStep(10.0, 8.0, 5.0, 2.0, p);
    double expected = p.a * 10.0 - p.b * std::pow(8.0, 2) + p.c * 5.0 + p.d * sin(2.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(SimulationTest, LinearProducesCorrectSequence) {
    ModelParams p;
    std::vector<double> u = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    auto y = simulateLinear(p, u);

    ASSERT_EQ(y.size(), p.time_steps + 1);
    EXPECT_NEAR(y[1], p.a * p.initial_temp + p.b * 5, 1e-9);
}

TEST(SimulationTest, NonlinearFirstStepUsesE) {
    ModelParams p;
    std::vector<double> u(p.time_steps, 5);
    auto y = simulateNonlinear(p, u);

    EXPECT_NEAR(y[1], p.initial_temp * p.INPUT_E, 1e-9);
}

TEST(SimulationTest, NonlinearHasDifferentDynamics) {
    ModelParams p;
    std::vector<double> u(p.time_steps, 5);
    auto y_lin = simulateLinear(p, u);
    auto y_nonlin = simulateNonlinear(p, u);

    // Проверим, что модели дают разный результат
    EXPECT_NE(y_lin.back(), y_nonlin.back());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
