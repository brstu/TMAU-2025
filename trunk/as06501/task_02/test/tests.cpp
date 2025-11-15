#include <gtest/gtest.h>
#include "lab1.h"
#include <cmath>

TEST(LinearModel, linear_all_zero) {
    EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(LinearModel, linear_y_only) {
    EXPECT_DOUBLE_EQ(linear(10, 0), a * 10);
}

TEST(LinearModel, linear_u_only) {
    EXPECT_DOUBLE_EQ(linear(0, 7), b * 7);
}

TEST(LinearModel, linear_general_case) {
    EXPECT_DOUBLE_EQ(linear(10, 7), a * 10 + b * 7);
}

TEST(NonLinearModel, nonlinear_all_zero) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinearModel, nonlinear_y_terms) {
    EXPECT_DOUBLE_EQ(nonlinear(6, 3, 0, 0), a * 6 - b * 3 * 3);
}

TEST(NonLinearModel, nonlinear_u_terms) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 4, 2), c * 4 + d * sin(2));
}

TEST(NonLinearModel, nonlinear_full_case) {
    EXPECT_DOUBLE_EQ(nonlinear(6, 3, 4, 2), a * 6 - b * 3 * 3 + c * 4 + d * sin(2));
}
