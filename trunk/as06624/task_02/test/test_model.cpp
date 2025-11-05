#include <gtest/gtest.h>
#include "model.h"

// -------------------------
// Тесты для linear_model
// -------------------------
TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.2), 0.0);
}

TEST(LinearModelTest, StepInput) {
    // y=1, u=1, a=0.8, b=0.2 → 0.8*1 + 0.2*1 = 1.0
    EXPECT_DOUBLE_EQ(linear_model(1.0, 1.0, 0.8, 0.2), 1.0);
}

TEST(LinearModelTest, OnlyControl) {
    // y=0, u=2, a=0.8, b=0.2 → 0 + 0.4 = 0.4
    EXPECT_DOUBLE_EQ(linear_model(0.0, 2.0, 0.8, 0.2), 0.4);
}

// -------------------------
// Тесты для nonlinear_model
// -------------------------
TEST(NonlinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear_model(0.0, 0.0, 0.0, 0.0, 0.8, 0.2, 0.1, 0.05), 0.0);
}

TEST(NonlinearModelTest, StepInput) {
    // y=1, y_prev=1, u=1, u_prev=0
    // 0.8*1 - 0.2*1^2 + 0.1*1 + 0.05*sin(0) = 0.7
    EXPECT_NEAR(nonlinear_model(1.0, 1.0, 1.0, 0.0, 0.8, 0.2, 0.1, 0.05), 0.7, 1e-9);
}

TEST(NonlinearModelTest, WithPrevControl) {
    // y=0.5, y_prev=0.5, u=1, u_prev=1
    double result = nonlinear_model(0.5, 0.5, 1.0, 1.0, 0.8, 0.2, 0.1, 0.05);
    // 0.8*0.5 - 0.2*0.25 + 0.1*1 + 0.05*sin(1)
    double expected = 0.4 - 0.05 + 0.1 + 0.05*std::sin(1.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

// -------------------------
// main для запуска тестов
// -------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}