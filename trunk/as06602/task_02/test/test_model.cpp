#include <gtest/gtest.h>
#include "model.h"
#include <cmath>

class ModelTest : public ::testing::Test {
protected:
    const double A = 0.8;
    const double B = 0.1;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y0 = 20.0;
    const double U0 = 5.0;
};

TEST_F(ModelTest, LinearModelBasicCalculation) {
    double expected = A * Y0 + B * U0;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y0, U0), expected);
}

TEST_F(ModelTest, LinearModelZeroValues) {
    EXPECT_DOUBLE_EQ(linearModel(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST_F(ModelTest, LinearModelNegativeValues) {
    const double A_NEG = -0.5;
    const double B_NEG = -0.2;
    const double Y_NEG = -10.0;
    const double U_NEG = -3.0;
    double expected = A_NEG * Y_NEG + B_NEG * U_NEG;
    EXPECT_DOUBLE_EQ(linearModel(A_NEG, B_NEG, Y_NEG, U_NEG), expected);
}

TEST_F(ModelTest, NonlinearModelBasicCalculation) {
    const double U_PREV = 4.0;
    double expected = A * Y0 - B_NL * Y0 * Y0 + C * U0 + D * sin(U_PREV);
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y0, U0, U_PREV), expected);
}

TEST_F(ModelTest, NonlinearModelZeroValues) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST_F(ModelTest, NonlinearModelSinZero) {
    EXPECT_DOUBLE_EQ(nonlinearModel(1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0), 0.0);
}

TEST_F(ModelTest, SimulateLinearSingleStep) {
    const int N = 1;
    auto result = simulateLinear(N, A, B, Y0, U0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    EXPECT_DOUBLE_EQ(result[1], linearModel(A, B, Y0, U0));
}

TEST_F(ModelTest, SimulateLinearMultipleSteps) {
    const int N = 3;
    auto result = simulateLinear(N, A, B, Y0, U0);
    ASSERT_EQ(result.size(), 4);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    for (int t = 1; t <= N; t++) {
        EXPECT_DOUBLE_EQ(result[t], linearModel(A, B, result[t-1], U0));
    }
}

TEST_F(ModelTest, SimulateNonlinearSingleStep) {
    const int N = 1;
    auto result = simulateNonlinear(N, A, B_NL, C, D, Y0, U0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    EXPECT_DOUBLE_EQ(result[1], nonlinearModel(A, B_NL, C, D, Y0, U0, U0));
}

TEST_F(ModelTest, SimulateNonlinearMultipleSteps) {
    const int N = 2;
    auto result = simulateNonlinear(N, A, B_NL, C, D, Y0, U0);
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    for (int t = 1; t <= N; t++) {
        EXPECT_DOUBLE_EQ(result[t], nonlinearModel(A, B_NL, C, D, result[t-1], U0, U0));
    }
}

TEST_F(ModelTest, SimulateLinearEdgeCaseNZero) {
    EXPECT_DEATH(simulateLinear(0, A, B, Y0, U0), "n must be positive");
}

TEST_F(ModelTest, SimulateNonlinearEdgeCaseNZero) {
    EXPECT_DEATH(simulateNonlinear(0, A, B_NL, C, D, Y0, U0), "n must be positive");
}