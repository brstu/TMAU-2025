#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

TEST(LinearStepTest, BasicBehavior) {
    ModelParams params;
    double result = linearStep(10.0, 5.0, params);
    EXPECT_NEAR(result, params.a * 10.0 + params.b * 5.0, 1e-9);
}

TEST(NonlinearStepTest, IncludesSinAndSquareTerms) {
    ModelParams params;
    double result = nonlinearStep(10.0, 8.0, 5.0, 2.0, params);
    double expected = params.a * 10.0 - params.b * std::pow(8.0, 2) + params.c * 5.0 + params.d * sin(2.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(SimulationTest, LinearProducesCorrectSequence) {
    ModelParams params;
    std::vector<double> u = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
    auto y = simulateLinear(params, u);

    ASSERT_EQ(y.size(), params.time_steps + 1);
    EXPECT_NEAR(y[1], params.a * params.initial_temp + params.b * 5, 1e-9);
}

TEST(SimulationTest, NonlinearFirstStepUsesE) {
    ModelParams params;
    std::vector<double> u(params.time_steps, 5);
    auto y = simulateNonlinear(params, u);

    EXPECT_NEAR(y[1], params.initial_temp * params.INPUT_E, 1e-9);
}

TEST(SimulationTest, NonlinearHasDifferentDynamics) {
    ModelParams params;
    std::vector<double> u(params.time_steps, 5);
    auto y_lin = simulateLinear(params, u);
    auto y_nonlin = simulateNonlinear(params, u);

    // Check that both models yield the expected values ​​at the final step
    // For the linear model: y[n] = ... (calculated using the formula)
    double expected_lin = params.initial_temp;
    for (int i = 0; i < params.time_steps; ++i) {
        expected_lin = params.a * expected_lin + params.b * u[i];
    }
    EXPECT_NEAR(y_lin.back(), expected_lin, 1e-9);

    // For a nonlinear model: y[n] = ... (calculated using the formula)
    double expected_nonlin = params.initial_temp;
    for (int i = 0; i < params.time_steps; ++i) {
        if (i == 0) {
            expected_nonlin = expected_nonlin * params.INPUT_E;
        } else {
            expected_nonlin = params.a * expected_nonlin
                - params.b * std::pow(expected_nonlin, 2)
                + params.c * u[i]
                + params.d * sin(u[i]);
        }
    }
    EXPECT_NEAR(y_nonlin.back(), expected_nonlin, 1e-9);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

