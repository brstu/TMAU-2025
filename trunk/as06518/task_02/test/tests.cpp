#include <gtest/gtest.h>
#include "func.h"

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(18, 0), PARAM_A * 18);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), PARAM_B * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(18, 5), PARAM_A * 18 + PARAM_B * 5);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(18, 18, 0, 0),
        PARAM_A * 18 - PARAM_B * pow(18, 2)
    );
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(0, 0, 5, 5),
        PARAM_C * 5 + PARAM_D * sin(5)
    );
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(18, 18, 5, 5),
        PARAM_A * 18 - PARAM_B * pow(18, 2) +
        PARAM_C * 5 + PARAM_D * sin(5)
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
