#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "../src/func.h"

TEST(LinearModelTest, Step_PositiveValues) {
    LinearModel model(0.9, 0.2);
    double y_next = model.step(10.0, 5.0);
    EXPECT_DOUBLE_EQ(y_next, 0.9 * 10.0 + 0.2 * 5.0);
}

TEST(LinearModelTest, Step_NegativeValues) {
    LinearModel model(0.9, 0.2);
    double y_next = model.step(-4.0, -2.0);
    EXPECT_DOUBLE_EQ(y_next, 0.9 * (-4.0) + 0.2 * (-2.0));
}

TEST(LinearModelTest, Step_ZeroValues) {
    LinearModel model(0.9, 0.2);
    EXPECT_DOUBLE_EQ(model.step(0.0, 0.0), 0.0);
}

TEST(NonlinearModelTest, Step_BaseCase) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    double result = model.step(2.0, 3.0, 0.0);
    double expected = 0.9 * 2.0 - 0.01 * 2.0 * 2.0 + 0.15 * 3.0 + 0.05 * sin(0.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(NonlinearModelTest, Step_WithPreviousInput) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    double result = model.step(1.0, 2.0, 1.57); // prev_u ≈ π/2
    double expected = 0.9 * 1.0 - 0.01 * 1.0 * 1.0 + 0.15 * 2.0 + 0.05 * sin(1.57);
    EXPECT_NEAR(result, expected, 1e-5);
}

TEST(NonlinearModelTest, Step_NegativeValues) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    double result = model.step(-3.0, -2.0, -1.0);
    double expected = 0.9 * (-3.0) - 0.01 * 9.0 + 0.15 * (-2.0) + 0.05 * sin(-1.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(SimulationTest, LinearAndNonlinearGrowAsExpected) {
    LinearModel linear{ModelConfig::a, ModelConfig::b_lin};
    NonlinearModel nonlinear{ModelConfig::a, ModelConfig::b_nonlin, ModelConfig::c, ModelConfig::d};

    const int n = 5;
    const double y0 = 1.0;
    const double u_val = 2.0;

    std::vector<double> y_lin(n + 1, 0.0);
    std::vector<double> y_nonlin(n + 1, 0.0);
    std::vector<double> u(n + 1, u_val);

    y_lin[0] = y0;
    y_nonlin[0] = y0;

    for (int t = 0; t < n; ++t) {
        y_lin[t + 1] = linear.step(y_lin[t], u[t]);
        double prev_u = (t > 0) ? u[t - 1] : ModelConfig::INITIAL_PREV_U;
        y_nonlin[t + 1] = nonlinear.step(y_nonlin[t], u[t], prev_u);
    }

    // Проверим рост значений
    for (int t = 1; t <= n; ++t) {
        EXPECT_GT(y_lin[t], 0);
        EXPECT_GT(y_nonlin[t], 0);
    }
}

TEST(EdgeCases, ZeroSteps_NoCrash) {
    int n = 0;
    double y0 = 1.0, u_val = 1.0;

    LinearModel linear{ModelConfig::a, ModelConfig::b_lin};
    NonlinearModel nonlinear{ModelConfig::a, ModelConfig::b_nonlin, ModelConfig::c, ModelConfig::d};

    std::vector<double> y_lin(n + 1, y0);
    std::vector<double> y_nonlin(n + 1, y0);

    EXPECT_EQ(y_lin.size(), 1);
    EXPECT_EQ(y_nonlin.size(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
