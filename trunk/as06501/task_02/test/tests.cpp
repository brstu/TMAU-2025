#include <gtest/gtest.h>
#include "func.h"

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linear(10, 0), a * 10);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linear(0, 5), b * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linear(10, 4), a * 10 + b * 4);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(nonlinear(10, 10, 0, 0), a * 10 - b * pow(10, 2));
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 4, 4), c * 4 + d * sin(4));
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinear(10, 10, 4, 4),
        a * 10 - b * pow(10, 2) + c * 4 + d * sin(4)
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
