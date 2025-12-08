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

    // Проверим, что обе модели дают ожидаемые значения на последнем шаге
    // Для линейной модели: y[n] = ... (расчет по формуле)
    double expected_lin = p.initial_temp;
    for (int i = 0; i < p.time_steps; ++i) {
        expected_lin = p.a * expected_lin + p.b * u[i];
    }
    EXPECT_NEAR(y_lin.back(), expected_lin, 1e-9);

    // Для нелинейной модели: y[n] = ... (расчет по формуле)
    double expected_nonlin = p.initial_temp;
    for (int i = 0; i < p.time_steps; ++i) {
        if (i == 0) {
            expected_nonlin = expected_nonlin * p.INPUT_E;
        } else {
            expected_nonlin = p.a * expected_nonlin
                - p.b * std::pow(expected_nonlin, 2)
                + p.c * u[i]
                + p.d * sin(u[i]);
        }
    }
    EXPECT_NEAR(y_nonlin.back(), expected_nonlin, 1e-9);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
