#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

TEST(Linear, test_zero) {
    EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(Linear, test_u0) {
    EXPECT_DOUBLE_EQ(linear(18, 0), a * 18);
}

TEST(Linear, test_y0) {
    EXPECT_DOUBLE_EQ(linear(0, 5), b * 5);
}

TEST(Linear, test_default) {
    EXPECT_DOUBLE_EQ(linear(18, 5), a * 18 + b * 5);
}

TEST(NonLinear, test_zero) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinear, test_u0) {
    EXPECT_DOUBLE_EQ(nonlinear(18, 18, 0, 0), a * 18 - b * std::pow(18, 2));
}

TEST(NonLinear, test_y0) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 5, 5), c * 5 + d * std::sin(5));
}

TEST(NonLinear, test_default) {
    EXPECT_DOUBLE_EQ(nonlinear(18, 18, 5, 5),
                     a * 18 - b * std::pow(18, 2) + c * 5 + d * std::sin(5));
}
