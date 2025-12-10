#include <gtest/gtest.h>
#include "../src/model.h"
#include <cmath>


TEST(LinearStepTest, ZeroInputGivesZeroOutput) {
    LinearParams p{0.86, 0.23};
    EXPECT_DOUBLE_EQ(linear_step(0.0, 0.0, p), 0.0);
}

TEST(LinearStepTest, WorksWithPositiveValues) {
    LinearParams p{0.5, 0.25};
    EXPECT_DOUBLE_EQ(linear_step(2.0, 4.0, p), 0.5 * 2.0 + 0.25 * 4.0);
}

TEST(LinearStepTest, WorksWithNegativeValues) {
    LinearParams p{0.8, 0.2};
    EXPECT_DOUBLE_EQ(linear_step(-3.0, -2.0, p), 0.8 * -3.0 + 0.2 * -2.0);
}


TEST(NonlinearStepTest, NonlinearIncludesSinCorrectly) {
    NonlinearParams p{0.69, 0.15, 0.10, 0.21};
    double y1 = 1.0;
    double y2 = 1.0;
    double u1 = 1.0;
    double u2 = 0.0;

    double expected = p.a * y1 - p.bnl * (y2 * y2) + p.c * u1 + p.d * std::sin(u2);

    EXPECT_NEAR(nonlinear_step(y1, y2, u1, u2, p), expected, 1e-9);
}

TEST(NonlinearStepTest, HandlesNegativeAndPositiveMix) {
    NonlinearParams p{0.7, 0.2, 0.1, 0.05};

    double result = nonlinear_step(-2.0, 1.0, 3.0, -1.0, p);

    double expected = 0.7 * -2.0 - 0.2 * (1.0 * 1.0) + 0.1 * 3.0 + 0.05 * std::sin(-1.0);

    EXPECT_NEAR(result, expected, 1e-9);
}
