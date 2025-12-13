#include <gtest/gtest.h>
#include "functions.h"
#include <cmath>


TEST(Linear, test_zero) {
    EXPECT_EQ(linear(0, 0), 0);
}

TEST(Linear, test_u0) {
    EXPECT_EQ(linear(18, 0), a * 18);
}

TEST(Linear, test_y0) {
    EXPECT_EQ(linear(0, 5), b * 5);
}

TEST(Linear, test_default) {
    EXPECT_EQ(linear(18, 5), a * 18 + b * 5);
}

TEST(Linear, test_negative_values) {
    EXPECT_EQ(linear(-10, -5), a * (-10) + b * (-5));
}

TEST(Linear, test_fractional_values) {
    EXPECT_DOUBLE_EQ(linear(2.5, 3.7), a * 2.5 + b * 3.7);
}

TEST(Linear, test_large_values) {
    EXPECT_EQ(linear(1000, 500), a * 1000 + b * 500);
}

// Тесты для нелинейной модели
TEST(NonLinear, test_zero) {
    EXPECT_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinear, test_u0) {
    EXPECT_DOUBLE_EQ(nonlinear(18, 18, 0, 0), a * 18 - b * 18 * 18);
}

TEST(NonLinear, test_y0) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 5, 5), c * 5 + d * sin(5));
}

TEST(NonLinear, test_default) {
    EXPECT_DOUBLE_EQ(nonlinear(18, 18, 5, 5), a * 18 - b * 18 * 18 + c * 5 + d * sin(5));
}

TEST(NonLinear, test_negative_inputs) {
    EXPECT_DOUBLE_EQ(nonlinear(-5, -3, -2, -1),
        a * (-5) - b * (-3) * (-3) + c * (-2) + d * sin(-1));
}

TEST(NonLinear, test_different_yt_yt1) {
    EXPECT_DOUBLE_EQ(nonlinear(10, 5, 3, 2),
        a * 10 - b * 5 * 5 + c * 3 + d * sin(2));
}

TEST(NonLinear, test_fractional_values) {
    EXPECT_DOUBLE_EQ(nonlinear(2.5, 1.5, 3.7, 0.5),
        a * 2.5 - b * 1.5 * 1.5 + c * 3.7 + d * sin(0.5));
}

TEST(NonLinear, test_large_values) {
    EXPECT_DOUBLE_EQ(nonlinear(100, 50, 25, 10),
        a * 100 - b * 50 * 50 + c * 25 + d * sin(10));
}

// Тест на точность вычислений с плавающей точкой
TEST(NonLinear, test_precision) {
    double result = nonlinear(1.234567, 2.345678, 3.456789, 4.567890);
    double expected = a * 1.234567 - b * 2.345678 * 2.345678 + c * 3.456789 + d * sin(4.567890);
    EXPECT_NEAR(result, expected, 1e-10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

