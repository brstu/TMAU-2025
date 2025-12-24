#include <gtest/gtest.h>
#include "model.h"

// -------------------------
// Тесты для linear_model
// -------------------------
TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.2), 0.0);
}

TEST(LinearModelTest, OnlyControl) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 2.0, 0.8, 0.2), 0.4);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear_model(-1.0, -1.0, 0.8, 0.2), -1.0);
}

// -------------------------
// Тесты для nonlinear_model
// -------------------------
TEST(NonlinearModelTest, ZeroInput) {
    State s{0.0, 0.0, 0.0, 0.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    EXPECT_DOUBLE_EQ(nonlinear_model(s, p), 0.0);
}

TEST(NonlinearModelTest, StepInput) {
    State s{1.0, 1.0, 1.0, 0.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    EXPECT_NEAR(nonlinear_model(s, p), 0.7, 1e-9);
}

TEST(NonlinearModelTest, WithPrevControl) {
    State s{0.5, 0.5, 1.0, 1.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    double expected = 0.8*0.5 - 0.2*0.25 + 0.1*1.0 + 0.05*std::sin(1.0);
    EXPECT_NEAR(nonlinear_model(s, p), expected, 1e-9);
}

TEST(NonlinearModelTest, NegativeInputs) {
    State s{-1.0, -1.0, -1.0, -1.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    double expected = 0.8*(-1.0) - 0.2*1.0 + 0.1*(-1.0) + 0.05*std::sin(-1.0);
    EXPECT_NEAR(nonlinear_model(s, p), expected, 1e-9);
}