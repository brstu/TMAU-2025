#include <gtest/gtest.h>
#include <cmath>
#include "functions.h"

using system_model::linear;
using system_model::nonlinear;
using system_model::a;
using system_model::b_lin;
using system_model::b_non;
using system_model::c;
using system_model::d;

// ---------- Linear model tests ----------

class LinearModelTest : public ::testing::Test {};

TEST_F(LinearModelTest, ComputesExpectedValue) {
    const double y = 10.0;
    const double u = 5.0;
    EXPECT_DOUBLE_EQ(linear(y, u), a * y + b_lin * u);
}

TEST_F(LinearModelTest, ZeroStateAndInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0), 0.0);
}

TEST_F(LinearModelTest, StateOnlyInfluence) {
    EXPECT_DOUBLE_EQ(linear(15.5, 0.0), a * 15.5);
}

TEST_F(LinearModelTest, InputOnlyInfluence) {
    EXPECT_DOUBLE_EQ(linear(0.0, 8.3), b_lin * 8.3);
}

TEST_F(LinearModelTest, HandlesNegativeArguments) {
    const double y = -5.0;
    const double u = -3.0;
    EXPECT_DOUBLE_EQ(linear(y, u), a * y + b_lin * u);
}

TEST_F(LinearModelTest, FractionalPrecision) {
    const double y = 2.75;
    const double u = 4.125;
    const double expected = a * y + b_lin * u;
    EXPECT_NEAR(linear(y, u), expected, 1e-12);
}

// ---------- Nonlinear model tests ----------

class NonlinearModelTest : public ::testing::Test {};

TEST_F(NonlinearModelTest, FullExpressionEvaluation) {
    const double yt  = 12.0;
    const double yt1 = 8.0;
    const double ut  = 6.0;
    const double ut1 = 4.0;

    const double expected =
        a * yt - b_non * yt1 * yt1 + c * ut + d * std::sin(ut1);

    EXPECT_DOUBLE_EQ(nonlinear(yt, yt1, ut, ut1), expected);
}

TEST_F(NonlinearModelTest, ZeroVectorCase) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST_F(NonlinearModelTest, DependsOnCurrentState) {
    EXPECT_DOUBLE_EQ(nonlinear(9.5, 0.0, 0.0, 0.0), a * 9.5);
}

TEST_F(NonlinearModelTest, DependsOnPreviousState) {
    const double y_prev = 7.2;
    EXPECT_DOUBLE_EQ(
        nonlinear(0.0, y_prev, 0.0, 0.0),
        -b_non * y_prev * y_prev
    );
}

TEST_F(NonlinearModelTest, DependsOnInputs) {
    const double ut  = 3.0;
    const double ut1 = 1.57;
    const double expected = c * ut + d * std::sin(ut1);

    EXPECT_NEAR(nonlinear(0.0, 0.0, ut, ut1), expected, 1e-12);
}

TEST_F(NonlinearModelTest, NegativeInputHandling) {
    const double result = nonlinear(4.0, 2.0, -3.0, -1.0);
    const double expected =
        a * 4.0 - b_non * 2.0 * 2.0 + c * (-3.0) + d * std::sin(-1.0);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST_F(NonlinearModelTest, HighPrecisionCheck) {
    const double yt  = 1.234567;
    const double yt1 = 9.876543;
    const double ut  = 2.718281;
    const double ut1 = 3.141592;

    const double expected =
        a * yt - b_non * yt1 * yt1 + c * ut + d * std::sin(ut1);

    EXPECT_NEAR(nonlinear(yt, yt1, ut, ut1), expected, 1e-10);
}

// ---------- System-level tests ----------

TEST(SystemSanity, ParametersAreInExpectedRange) {
    EXPECT_GT(a, 0.0);
    EXPECT_LT(a, 1.0);

    EXPECT_GT(b_lin, 0.0);
    EXPECT_GT(b_non, 0.0);
    EXPECT_GT(c, 0.0);
    EXPECT_GT(d, 0.0);
}

TEST(SystemSanity, LinearAndNonlinearDiffer) {
    const double y = 10.0;
    const double u = 5.0;

    const double lin = linear(y, u);
    const double nonlin = nonlinear(y, y, u, u);

    EXPECT_NE(lin, nonlin);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
