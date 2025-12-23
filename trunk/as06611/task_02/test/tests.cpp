#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>

// Тесты для линейной модели
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0.0, 0.0), 0.0);
}

TEST(LinearModel, OnlyYNonZero) {
    EXPECT_DOUBLE_EQ(linearModel(18.0, 0.0), A * 18.0);
}

TEST(LinearModel, OnlyUNonZero) {
    EXPECT_DOUBLE_EQ(linearModel(0.0, 5.0), B * 5.0);
}

TEST(LinearModel, TypicalValues) {
    EXPECT_DOUBLE_EQ(linearModel(18.0, 5.0), A * 18.0 + B * 5.0);
}

TEST(LinearModel, NegativeValues) {
    EXPECT_DOUBLE_EQ(linearModel(-10.0, -5.0), A * (-10.0) + B * (-5.0));
}

TEST(LinearModel, FractionalValues) {
    EXPECT_DOUBLE_EQ(linearModel(2.5, 3.7), A * 2.5 + B * 3.7);
}

TEST(LinearModel, LargeValues) {
    EXPECT_DOUBLE_EQ(linearModel(1000.0, 500.0), A * 1000.0 + B * 500.0);
}

// Тесты для нелинейной модели
TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModel, OnlyCurrentYNonZero) {
    EXPECT_DOUBLE_EQ(nonlinearModel(18.0, 0.0, 0.0, 0.0), A * 18.0);
}

TEST(NonlinearModel, OnlyPrevYNonZero) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0.0, 18.0, 0.0, 0.0), -B * pow(18.0, 2));
}

TEST(NonlinearModel, OnlyCurrentUNonZero) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0.0, 0.0, 5.0, 0.0), C_val * 5.0);
}

TEST(NonlinearModel, OnlyPrevUNonZero) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0.0, 0.0, 0.0, 5.0), D_val * sin(5.0));
}

TEST(NonlinearModel, TypicalValues) {
    double expected = A * 18.0 - B * pow(10.0, 2) + C_val * 5.0 + D_val * sin(3.0);
    EXPECT_DOUBLE_EQ(nonlinearModel(18.0, 10.0, 5.0, 3.0), expected);
}

TEST(NonlinearModel, NegativeInputs) {
    double expected = A * (-5.0) - B * pow(-3.0, 2) + C_val * (-2.0) + D_val * sin(-1.0);
    EXPECT_DOUBLE_EQ(nonlinearModel(-5.0, -3.0, -2.0, -1.0), expected);
}

TEST(NonlinearModel, FractionalValues) {
    double expected = A * 2.5 - B * pow(1.5, 2) + C_val * 3.7 + D_val * sin(0.5);
    EXPECT_DOUBLE_EQ(nonlinearModel(2.5, 1.5, 3.7, 0.5), expected);
}

TEST(NonlinearModel, LargeValues) {
    double expected = A * 100.0 - B * pow(50.0, 2) + C_val * 25.0 + D_val * sin(10.0);
    EXPECT_DOUBLE_EQ(nonlinearModel(100.0, 50.0, 25.0, 10.0), expected);
}

TEST(NonlinearModel, PrecisionCheck) {
    double result = nonlinearModel(1.234567, 2.345678, 3.456789, 4.567890);
    double expected = A * 1.234567 - B * pow(2.345678, 2) + C_val * 3.456789 + D_val * sin(4.567890);
    EXPECT_NEAR(result, expected, 1e-10);
}
// Тест для проверки работы с константами
TEST(ConstantsCheck, VerifyConstants) {
    EXPECT_EQ(N, 15);
    EXPECT_DOUBLE_EQ(A, 0.9);
    EXPECT_DOUBLE_EQ(B, 0.01);
    EXPECT_DOUBLE_EQ(C_val, 0.4);
    EXPECT_DOUBLE_EQ(D_val, 0.1);
    EXPECT_DOUBLE_EQ(Y_start, 20.0);
}
