#include <gtest/gtest.h>
#include "func.h"

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(18, 0), kA * 18);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), kB * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(18, 5), kA * 18 + kB * 5);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyYPrev) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(0, 4, 0, 0),
        kB * pow(4, 2)
    );
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(0, 0, 6, 6),
        kC * 6 + kD * sin(6)
    );
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(18, 18, 5, 5),
        kA * 18 + kB * pow(18, 2) + kC * 5 + kD * sin(5)
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
