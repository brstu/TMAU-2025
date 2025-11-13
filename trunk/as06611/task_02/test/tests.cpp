#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>

// Tests for linear model
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0), 0.0);
}

TEST(LinearModel, OnlyYNonZero) {
    EXPECT_DOUBLE_EQ(linear(18.0, 0.0), a * 18.0);
}

TEST(LinearModel, OnlyUNonZero) {
    EXPECT_DOUBLE_EQ(linear(0.0, 5.0), b * 5.0);
}

TEST(LinearModel, TypicalValues) {
    EXPECT_DOUBLE_EQ(linear(18.0, 5.0), a * 18.0 + b * 5.0);
}

TEST(LinearModel, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear(-10.0, -5.0), a * (-10.0) + b * (-5.0));
}

TEST(LinearModel, FractionalValues) {
    EXPECT_DOUBLE_EQ(linear(2.5, 3.7), a * 2.5 + b * 3.7);
}

TEST(LinearModel, LargeValues) {
    EXPECT_DOUBLE_EQ(linear(1000.0, 500.0), a * 1000.0 + b * 500.0);
}

// Тесты для нелинейной модели
TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModel, OnlyYNonZero) {
    EXPECT_DOUBLE_EQ(nonlinear(18.0, 18.0, 0.0, 0.0), a * 18.0 - b * 18.0 * 18.0);
}

TEST(NonlinearModel, OnlyUNonZero) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 5.0, 5.0), c * 5.0 + d * sin(5.0));
}

TEST(NonlinearModel, TypicalValues) {
    EXPECT_DOUBLE_EQ(nonlinear(18.0, 18.0, 5.0, 5.0),
                     a * 18.0 - b * 18.0 * 18.0 + c * 5.0 + d * sin(5.0));
}

TEST(NonlinearModel, NegativeInputs) {
    EXPECT_DOUBLE_EQ(nonlinear(-5.0, -3.0, -2.0, -1.0),
                     a * (-5.0) - b * (-3.0) * (-3.0) + c * (-2.0) + d * sin(-1.0));
}

TEST(NonlinearModel, DifferentYtYt1) {
    EXPECT_DOUBLE_EQ(nonlinear(10.0, 5.0, 3.0, 2.0),
                     a * 10.0 - b * 25.0 + c * 3.0 + d * sin(2.0));
}

TEST(NonlinearModel, FractionalValues) {
    EXPECT_DOUBLE_EQ(nonlinear(2.5, 1.5, 3.7, 0.5),
                     a * 2.5 - b * 1.5 * 1.5 + c * 3.7 + d * sin(0.5));
}

TEST(NonlinearModel, LargeValues) {
    EXPECT_DOUBLE_EQ(nonlinear(100.0, 50.0, 25.0, 10.0),
                     a * 100.0 - b * 2500.0 + c * 25.0 + d * sin(10.0));
}

TEST(NonlinearModel, PrecisionCheck) {
    double result = nonlinear(1.234567, 2.345678, 3.456789, 4.567890);
    double expected = a * 1.234567 - b * 2.345678 * 2.345678 + c * 3.456789 + d * sin(4.567890);
    EXPECT_NEAR(result, expected, 1e-10);
}

// Точка входа для запуска тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
