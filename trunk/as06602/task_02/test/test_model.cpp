#include <gtest/gtest.h>
#include "model.h"
#include <cmath>

TEST(LinearModelTest, BasicCalculation) {
    const double A = 0.8;
    const double B = 0.1;
    const double Y_T = 20.0;
    const double U_T = 5.0;
    double expected = A * Y_T + B * U_T;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y_T, U_T), expected);
}

TEST(LinearModelTest, ZeroValues) {
    const double A = 0.0;
    const double B = 0.0;
    const double Y_T = 0.0;
    const double U_T = 0.0;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y_T, U_T), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    const double A = -0.5;
    const double B = -0.2;
    const double Y_T = -10.0;
    const double U_T = -3.0;
    double expected = A * Y_T + B * U_T;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y_T, U_T), expected);
}

TEST(NonlinearModelTest, BasicCalculation) {
    const double A = 0.8;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y_T = 20.0;
    const double U_T = 5.0;
    const double U_PREV = 4.0;
    double expected = A * Y_T - B_NL * Y_T * Y_T + C * U_T + D * sin(U_PREV);
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y_T, U_T, U_PREV), expected);
}

TEST(NonlinearModelTest, ZeroValues) {
    const double A = 0.0;
    const double B_NL = 0.0;
    const double C = 0.0;
    const double D = 0.0;
    const double Y_T = 0.0;
    const double U_T = 0.0;
    const double U_PREV = 0.0;
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y_T, U_T, U_PREV), 0.0);
}

TEST(NonlinearModelTest, SinZero) {
    const double A = 1.0;
    const double B_NL = 0.0;
    const double C = 0.0;
    const double D = 1.0;
    const double Y_T = 0.0;
    const double U_T = 0.0;
    const double U_PREV = 0.0;
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y_T, U_T, U_PREV), 0.0);
}

TEST(SimulateLinearTest, SingleStep) {
    const int N = 1;
    const double A = 0.8;
    const double B = 0.1;
    const double Y0 = 20.0;
    const double U0 = 5.0;
    auto result = simulateLinear(N, A, B, Y0, U0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    EXPECT_DOUBLE_EQ(result[1], linearModel(A, B, Y0, U0));
}

TEST(SimulateLinearTest, MultipleSteps) {
    const int N = 3;
    const double A = 0.5;
    const double B = 0.2;
    const double Y0 = 10.0;
    const double U0 = 2.0;
    auto result = simulateLinear(N, A, B, Y0, U0);
    ASSERT_EQ(result.size(), 4);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    for (int t = 1; t <= N; t++) {
        EXPECT_DOUBLE_EQ(result[t], linearModel(A, B, result[t-1], U0));
    }
}

TEST(SimulateNonlinearTest, SingleStep) {
    const int N = 1;
    const double A = 0.8;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y0 = 20.0;
    const double U0 = 5.0;
    auto result = simulateNonlinear(N, A, B_NL, C, D, Y0, U0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    EXPECT_DOUBLE_EQ(result[1], nonlinearModel(A, B_NL, C, D, Y0, U0, U0));
}

TEST(SimulateNonlinearTest, MultipleSteps) {
    const int N = 2;
    const double A = 0.8;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y0 = 20.0;
    const double U0 = 5.0;
    auto result = simulateNonlinear(N, A, B_NL, C, D, Y0, U0);
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    for (int t = 1; t <= N; t++) {
        EXPECT_DOUBLE_EQ(result[t], nonlinearModel(A, B_NL, C, D, result[t-1], U0, U0));
    }
}