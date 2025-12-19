#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

using Model::linearModel;
using Model::nonlinearModel;

TEST(LinearModel, zero_case) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, only_y) {
    EXPECT_DOUBLE_EQ(linearModel(10, 0), a * 10);
}

TEST(LinearModel, only_u) {
    EXPECT_DOUBLE_EQ(linearModel(0, 4), b * 4);
}

TEST(LinearModel, mixed) {
    EXPECT_DOUBLE_EQ(linearModel(10, 4), a * 10 + b * 4);
}

TEST(NonlinearModel, zero_case) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, with_y) {
    EXPECT_DOUBLE_EQ(nonlinearModel(10, 10, 0, 0), a * 10 - b * std::pow(10, 2));
}

TEST(NonlinearModel, with_u) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 4, 4), c * 4 + d * std::sin(4));
}

TEST(NonlinearModel, mixed) {
    EXPECT_DOUBLE_EQ(nonlinearModel(10, 10, 4, 4),
                     a * 10 - b * std::pow(10, 2) + c * 4 + d * std::sin(4));
}
