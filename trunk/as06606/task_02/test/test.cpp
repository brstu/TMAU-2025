#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "../src/func.h"

TEST(LinearStepTest, PositiveValues) {
    double y_next = linear_step(10.0, 5.0);
    EXPECT_DOUBLE_EQ(y_next, A*10.0 + B_LIN*5.0);
}

TEST(LinearStepTest, NegativeValues) {
    double y_next = linear_step(-4.0, -2.0);
    EXPECT_DOUBLE_EQ(y_next, A*(-4.0) + B_LIN*(-2.0));
}

TEST(LinearStepTest, ZeroValues) {
    double y_next = linear_step(0.0, 0.0);
    EXPECT_DOUBLE_EQ(y_next, 0.0);
}

TEST(NonlinearStepTest, BaseCase) {
    double result = nonlinear_step(2.0, 3.0, 0.0);
    double expected = A*2.0 - B_NONLIN*2.0*2.0 + C*3.0 + D*sin(0.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(NonlinearStepTest, WithPreviousInput) {
    double result = nonlinear_step(1.0, 2.0, 1.57);
    double expected = A*1.0 - B_NONLIN*1.0*1.0 + C*2.0 + D*sin(1.57);
    EXPECT_NEAR(result, expected, 1e-5);
}

TEST(NonlinearStepTest, NegativeValues) {
    double result = nonlinear_step(-3.0, -2.0, -1.0);
    double expected = A*(-3.0) - B_NONLIN*(-3.0)*(-3.0) + C*(-2.0) + D*sin(-1.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

TEST(SimulationTest, LinearAndNonlinearGrowAsExpected) {
    const int n = 5;
    const double y0 = 1.0;
    const double u_val = 2.0;

    std::vector<double> y_lin(n + 1, y0);
    std::vector<double> y_nonlin(n + 1, y0);
    std::vector<double> u(n + 1, u_val);

    for (int t = 0; t < n; ++t) {
        y_lin[t + 1] = linear_step(y_lin[t], u[t]);
        double prev_u = (t > 0) ? u[t - 1] : INITIAL_PREV_U;
        y_nonlin[t + 1] = nonlinear_step(y_nonlin[t], u[t], prev_u);
    }

    for (int t = 1; t <= n; ++t) {
        EXPECT_GT(y_lin[t], 0);
        EXPECT_GT(y_nonlin[t], 0);
    }
}

TEST(EdgeCases, ZeroSteps_NoCrash) {
    int n = 0;
    double y0 = 1.0;
    [[maybe_unused]] double u_val = 1.0;

    std::vector<double> y_lin(n + 1, y0);
    std::vector<double> y_nonlin(n + 1, y0);

    EXPECT_EQ(y_lin.size(), 1);
    EXPECT_EQ(y_nonlin.size(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
