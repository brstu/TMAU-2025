#include <gtest/gtest.h>
#include "model_functions.h"

TEST(ModelFunctionsTest, CalcLinearBasic) {
    EXPECT_DOUBLE_EQ(calcLinear(10.0, 5.0), (Constants::A * 10.0) + (Constants::B * 5.0));
}

TEST(ModelFunctionsTest, CalcLinearZeroInput) {
    EXPECT_DOUBLE_EQ(calcLinear(0.0, 0.0), 0.0);
}

TEST(ModelFunctionsTest, CalcNonlinearBasic) {
    double currentY = 10.0;
    double prevY = 8.0;
    double inputU = 5.0;
    double prevU = 4.0;

    double expected = (Constants::A * currentY) - (Constants::B * prevY * prevY) + (Constants::C * inputU) + Constants::D * sin(prevU);
    EXPECT_DOUBLE_EQ(calcNonlinear(currentY, prevY, inputU, prevU), expected);
}

TEST(ModelFunctionsTest, CalcNonlinearZero) {
    EXPECT_DOUBLE_EQ(calcNonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}