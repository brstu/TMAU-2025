#include <gtest/gtest.h>
#include <cmath>
#include "func.h"

TEST(Linear, ZeroInputZeroState) {
    EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(Linear, NegativeValues) {
    double y = -10;
    double u = -3;
    EXPECT_DOUBLE_EQ(linear(y, u), LINEAR_A * y + LINEAR_B * u);
}

TEST(Linear, MonotonicityIncreaseInput) {
    // Если u2 > u1 и y одинаковые, выход должен вырасти
    double y = 5;
    double u1 = 1;
    double u2 = 3;

    double r1 = linear(y, u1);
    double r2 = linear(y, u2);

    EXPECT_GT(r2, r1);
}

TEST(Linear, MonotonicityIncreaseState) {
    // Если y2 > y1 при одинаковом u, выход должен вырасти
    double y1 = 2;
    double y2 = 5;
    double u = 4;

    EXPECT_GT(linear(y2, u), linear(y1, u));
}

TEST(NonLinear, ZeroEverything) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinear, OnlyTemperature) {
    // ut = 0, ut_1 = 0 → остаётся только a*y - b*(y1^2)
    double y = 4;
    double y1 = 4;

    EXPECT_DOUBLE_EQ(
        nonlinear(y, y1, 0, 0),
        NONLINEAR_A * y - NONLINEAR_B * y1 * y1
    );
}

TEST(NonLinear, OnlyHeating) {
    // y = 0 → остаётся c*ut + d*sin(ut_1)
    double ut = 3;
    double ut1 = 2;

    EXPECT_NEAR(
        nonlinear(0, 0, ut, ut1),
        NONLINEAR_C * ut + NONLINEAR_D * std::sin(ut1),
        1e-12
    );
}

TEST(NonLinear, NegativeInputs) {
    double y = -5;
    double y1 = -4;
    double ut = -2;
    double ut1 = -3;

    double expected = NONLINEAR_A * y 
                     - NONLINEAR_B * y1 * y1 
                     + NONLINEAR_C * ut 
                     + NONLINEAR_D * std::sin(ut1);

    EXPECT_NEAR(nonlinear(y, y1, ut, ut1), expected, 1e-12);
}

TEST(NonLinear, SensitivityToPreviousInput) {
    // Проверяем, что sin(ut1) реально влияет
    double y = 5, y1 = 4, ut = 2;

    double r1 = nonlinear(y, y1, ut, 0);
    double r2 = nonlinear(y, y1, ut, 1);

    EXPECT_NE(r1, r2);
}