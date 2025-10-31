#include <gtest/gtest.h>
#include "../src/model.h"
#include <cmath>


TEST(LinearModelTest, BasicCalculation) {
    double result = linear_model(2.0, 1.0, 0.5, 0.3);
    EXPECT_DOUBLE_EQ(result, 0.5 * 2.0 + 0.3 * 1.0);
}

TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.15), 0.0);
}

TEST(LinearModelTest, NegativeInput) {
    double result = linear_model(-2.0, -1.0, 0.5, 0.3);
    EXPECT_DOUBLE_EQ(result, 0.5 * -2.0 + 0.3 * -1.0);
}



TEST(NonlinearModelTest, BasicCalculation) {
    double y_t = 2.0, y_prev = 1.0, u_t = 1.0, u_prev = 0.0;
    double a = 0.8, b = 0.2, c = 0.1, d = 0.05;
    double expected = a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
    EXPECT_NEAR(nonlinear_model(y_t, y_prev, u_t, u_prev, a, b, c, d), expected, 1e-9);
}

TEST(NonlinearModelTest, ZeroValues) {
    EXPECT_DOUBLE_EQ(nonlinear_model(0, 0, 0, 0, 0.8, 0.2, 0.1, 0.05), 0.0);
}

TEST(NonlinearModelTest, LargeValuesFinite) {
    double result = nonlinear_model(100, 50, 10, 5, 0.9, 0.1, 0.2, 0.3);
    EXPECT_TRUE(std::isfinite(result));
}
