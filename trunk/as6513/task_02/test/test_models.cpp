#include <gtest/gtest.h>
#include "models.h"
#include <cmath>

TEST(LinearModelTest, ZeroInputs) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.15), 0.0);
}

TEST(LinearModelTest, BasicCase) {
    double result = linear_model(1.0, 1.0, 0.8, 0.15);
    EXPECT_NEAR(result, 0.95, 1e-9);
}

TEST(LinearModelTest, NegativeValues) {
    double result = linear_model(-2.0, -3.0, 0.8, 0.15);
    EXPECT_NEAR(result, -1.6 - 0.45, 1e-9);
}

TEST(NonlinearModelTest, ZeroInputs) {
    double result = nonlinear_model(0.0, 0.0, 0.0, 0.0,
                                    0.8, 0.15, 0.05, 0.1);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, BasicCase) {
    double r = nonlinear_model(1.0, 1.0, 1.0, 1.0,
                               0.8, 0.15, 0.05, 0.1);
    double expected = 0.8 - 0.15 + 0.05 + 0.1 * sin(1.0);
    EXPECT_NEAR(r, expected, 1e-9);
}

TEST(NonlinearModelTest, NonlinearEffect) {
    double r1 = nonlinear_model(1.0, 1.0, 0.0, 0.0, 0.8, 0.15, 0.05, 0.1);
    double r2 = nonlinear_model(1.0, 2.0, 0.0, 0.0, 0.8, 0.15, 0.05, 0.1);
    EXPECT_LT(r2, r1); // из-за -b*y_prev^2
}
