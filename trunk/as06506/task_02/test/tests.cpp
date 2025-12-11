#include <gtest/gtest.h>
#include "func.h"

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(20, 0), A * 20);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), B * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(20, 4), A * 20 + B * 4);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(nonlinearModel(20, 20, 0, 0),
        A * 20 - B * pow(20, 2));
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 5, 5),
        C * 5 + D * sin(5));
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(20, 20, 4, 4),
        A * 20 - B * pow(20, 2) + C * 4 + D * sin(4)
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
