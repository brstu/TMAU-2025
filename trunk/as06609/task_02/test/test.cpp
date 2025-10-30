#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

TEST(Linear, test_zero) {
    EXPECT_EQ(linear(0,0), 0);
}

TEST(Linear, test_u0) {
    EXPECT_EQ(linear(18,0), A*18);
}

TEST(Linear, test_y0) {
    EXPECT_EQ(linear(0, 5), B * 5);
}

TEST(Linear, test_default) {
    EXPECT_EQ(linear(18, 5), A*18 + B*5);
}

TEST(NonLinear, test_zero) {
    EXPECT_EQ(nonlinear(0,0,0,0), 0);
}

TEST(NonLinear, test_u0) {
    EXPECT_EQ(nonlinear(18, 18, 0, 0), A*18 - B * pow(18, 2));
}

TEST(NonLinear, test_y0) {
    EXPECT_EQ(nonlinear(0, 0, 5, 5), C * 5 + D * sin(5));
}

TEST(NonLinear, test_default) {
    EXPECT_EQ(nonlinear(18, 18, 5, 5), A*18 - B * pow(18, 2) + C * 5 + D * sin(5));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
