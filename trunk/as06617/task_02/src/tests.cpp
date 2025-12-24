#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

using namespace model_params;

// ===== Linear model tests =====

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0), 0.0);
}

TEST(LinearModel, ZeroControl) {
    const double y = INITIAL_Y;
    EXPECT_DOUBLE_EQ(linear(y, 0.0), A * y);
}

TEST(LinearModel, ZeroState) {
    const double u = 5.0;
    EXPECT_DOUBLE_EQ(linear(0.0, u), B * u);
}

TEST(LinearModel, TypicalValues) {
    const double y = INITIAL_Y;
    const double u = 5.0;
    EXPECT_DOUBLE_EQ(linear(y, u), A * y + B * u);
}

// ===== Nonlinear model tests =====

TEST(NonLinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonLinearModel, ZeroControlSignal) {
    const double y = INITIAL_Y;
    EXPECT_DOUBLE_EQ(
        nonlinear(y, y, 0.0, 0.0),
        A * y - B * (y * y)
    );
}

TEST(NonLinearModel, ZeroStateValue) {
    const double u = 5.0;
    EXPECT_DOUBLE_EQ(
        nonlinear(0.0, 0.0, u, u),
        C * u + D * std::sin(u)
    );
}

TEST(NonLinearModel, TypicalValues) {
    const double y = INITIAL_Y;
    const double u = 5.0;

    const double expected =
        A * y - B * (y * y) +
        C * u + D * std::sin(u);

    EXPECT_DOUBLE_EQ(nonlinear(y, y, u, u), expected);
}
