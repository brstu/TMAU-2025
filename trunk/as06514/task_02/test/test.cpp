#include <gtest/gtest.h>
#include <cmath>
#include "function.h"

TEST(LinearModelTest, BasicCalculation) {
    double result = linear(10.0, 5.0);
    EXPECT_DOUBLE_EQ(result, a_lin * 10.0 + b_lin * 5.0);
}

TEST(LinearModelTest, ZeroInput) {
    double result = linear(0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, BasicCalculation) {
    double yt = 10.0;
    double yt_1 = 8.0;
    double ut = 5.0;
    double ut_1 = 3.0;

    double expected = a_nonlin * yt - b_nonlin * pow(yt_1, 2) + c_nonlin * ut + d_nonlin * sin(ut_1);
    double result = nonlinear(yt, yt_1, ut, ut_1);

    EXPECT_NEAR(result, expected, 1e-10);
}

TEST(NonlinearModelTest, ZeroInputs) {
    double result = nonlinear(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(ConstantsTest, ValuesInRange) {
    EXPECT_GT(a_lin, 0);
    EXPECT_LT(a_lin, 1);
    EXPECT_GT(b_lin, 0);
    EXPECT_LT(b_lin, 1);
}

TEST(StepResponseTest, Convergence) {
    double yt = 0.0;
    for (int i = 0; i < 100; i++) {
        yt = linear(yt, 1.0);
    }

    double steady_state = b_lin / (1 - a_lin);
    EXPECT_NEAR(yt, steady_state, 1e-6);
}
