#include <gtest/gtest.h>
#include <cmath>
#include "func.h"

using namespace TemperatureModels;
using namespace ModelConstants;

TEST(LinearModelTest, ZeroInputZeroState) {
    EXPECT_DOUBLE_EQ(computeLinearModel(0, 0), 0);
}

TEST(LinearModelTest, NegativeValues) {
    double y = -10;
    double u = -3;
    EXPECT_DOUBLE_EQ(computeLinearModel(y, u), LINEAR_A * y + LINEAR_B * u);
}

TEST(LinearModelTest, MonotonicityIncreaseInput) {
    double y = 5;
    double u1 = 1;
    double u2 = 3;
    double r1 = computeLinearModel(y, u1);
    double r2 = computeLinearModel(y, u2);
    EXPECT_GT(r2, r1);
}

TEST(LinearModelTest, MonotonicityIncreaseState) {
    double y1 = 2;
    double y2 = 5;
    double u = 4;
    EXPECT_GT(computeLinearModel(y2, u), computeLinearModel(y1, u));
}

TEST(LinearModelTest, LinearCoefficientVerification) {
    // Проверка, что коэффициенты работают как ожидается
    double y = 10.0;
    double u = 5.0;
    double expected = 0.9 * 10.0 + 0.01 * 5.0; // LINEAR_A * y + LINEAR_B * u
    EXPECT_DOUBLE_EQ(computeLinearModel(y, u), expected);
}

TEST(NonLinearModelTest, ZeroEverything) {
    EXPECT_DOUBLE_EQ(computeNonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonLinearModelTest, OnlyTemperature) {
    double y = 4;
    double y_prev = 4;
    EXPECT_DOUBLE_EQ(
        computeNonlinearModel(y, y_prev, 0, 0),
        NONLINEAR_A * y - NONLINEAR_B * std::pow(y_prev, 2)
    );
}

TEST(NonLinearModelTest, OnlyHeating) {
    double u_current = 3;
    double u_prev = 2;
    EXPECT_NEAR(
        computeNonlinearModel(0, 0, u_current, u_prev),
        NONLINEAR_C * u_current + NONLINEAR_D * std::sin(u_prev),
        1e-12
    );
}

TEST(NonLinearModelTest, NegativeInputs) {
    double y = -5;
    double y_prev = -4;
    double u_current = -2;
    double u_prev = -3;
    double expected = NONLINEAR_A * y 
                     - NONLINEAR_B * std::pow(y_prev, 2)
                     + NONLINEAR_C * u_current 
                     + NONLINEAR_D * std::sin(u_prev);
    EXPECT_NEAR(computeNonlinearModel(y, y_prev, u_current, u_prev), 
                expected, 1e-12);
}

TEST(NonLinearModelTest, SensitivityToPreviousInput) {
    double y = 5;
    double y_prev = 4;
    double u_current = 2;
    double r1 = computeNonlinearModel(y, y_prev, u_current, 0);
    double r2 = computeNonlinearModel(y, y_prev, u_current, 1);
    EXPECT_NE(r1, r2);
}

TEST(NonLinearModelTest, SinFunctionEffect) {
    // Проверка, что синус действительно влияет на результат
    double y = 1;
    double y_prev = 1;
    double u_current = 1;
    
    // При разных предыдущих управлениях результат должен отличаться
    double result1 = computeNonlinearModel(y, y_prev, u_current, 0);
    double result2 = computeNonlinearModel(y, y_prev, u_current, M_PI/2); // sin(π/2) = 1
    double result3 = computeNonlinearModel(y, y_prev, u_current, M_PI);   // sin(π) = 0
    
    EXPECT_NE(result1, result2);
    EXPECT_NE(result1, result3);
    EXPECT_NE(result2, result3);
}

TEST(NonLinearModelTest, QuadraticTermEffect) {
    // Проверка квадратичного члена
    double y = 2;
    double u_current = 1;
    double u_prev = 1;
    
    // При разных предыдущих температурах результат должен отличаться
    double result1 = computeNonlinearModel(y, 1, u_current, u_prev);  // y_prev = 1
    double result2 = computeNonlinearModel(y, 2, u_current, u_prev);  // y_prev = 2
    double result3 = computeNonlinearModel(y, 3, u_current, u_prev);  // y_prev = 3
    
    EXPECT_NE(result1, result2);
    EXPECT_NE(result1, result3);
    EXPECT_NE(result2, result3);
}

TEST(NonLinearModelTest, CombinedEffects) {
    // Комплексный тест со всеми компонентами
    double y = 3.0;
    double y_prev = 2.0;
    double u_current = 1.5;
    double u_prev = 0.8;
    
    double expected = NONLINEAR_A * y 
                     - NONLINEAR_B * std::pow(y_prev, 2)
                     + NONLINEAR_C * u_current 
                     + NONLINEAR_D * std::sin(u_prev);
    
    EXPECT_NEAR(computeNonlinearModel(y, y_prev, u_current, u_prev), 
                expected, 1e-12);
}

TEST(ConstantsTest, VerifyConstantValues) {
    // Проверка значений констант
    EXPECT_DOUBLE_EQ(LINEAR_A, 0.9);
    EXPECT_DOUBLE_EQ(LINEAR_B, 0.01);
    EXPECT_DOUBLE_EQ(NONLINEAR_A, 0.9);
    EXPECT_DOUBLE_EQ(NONLINEAR_B, 0.01);
    EXPECT_DOUBLE_EQ(NONLINEAR_C, 0.15);
    EXPECT_DOUBLE_EQ(NONLINEAR_D, 0.05);
    EXPECT_DOUBLE_EQ(ZERO_PREV_INPUT, 0.0);
}