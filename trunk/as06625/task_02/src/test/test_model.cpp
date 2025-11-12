#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

TEST(LinearModelTest, BaseValues) {
    Params prm;
    std::vector<double> input(10, 4.0);
    auto y = lin_model(prm, input);

    EXPECT_EQ(y.size(), prm.steps + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
}

TEST(LinearModelTest, ZeroInput) {
    Params prm;
    std::vector<double> input(10, 0.0);
    auto y = lin_model(prm, input);

    EXPECT_NEAR(y[1], 25.0 * prm.alpha, 1e-6);
    EXPECT_NEAR(y[2], 25.0 * prm.alpha * prm.alpha, 1e-6);
}

TEST(LinearModelTest, InsufficientInput) {
    Params prm;
    std::vector<double> input(prm.steps - 1, 1.0);
    EXPECT_THROW(lin_model(prm, input), std::invalid_argument);
}


TEST(NonlinearModelTest, StartValues) {
    Params prm;
    std::vector<double> input(10, 4.0);
    auto y = nonlin_model(prm, input);

    EXPECT_EQ(y.size(), prm.steps + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
    EXPECT_DOUBLE_EQ(y[1], 25.0);
}

TEST(NonlinearModelTest, InputInfluence) {
    Params prm;
    std::vector<double> u1(10, 4.0);
    std::vector<double> u2(10, 8.0);

    auto y1 = nonlin_model(prm, u1);
    auto y2 = nonlin_model(prm, u2);

    EXPECT_GT(y2.back(), y1.back());
}

TEST(NonlinearModelTest, OutputChanges) {
    Params prm;
    std::vector<double> input = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto y = nonlin_model(prm, input);

    bool all_equal = true;
    for (int i = 1; i < static_cast<int>(y.size()); ++i) {
        if (std::fabs(y[i] - y[0]) > 1e-9) {
            all_equal = false;
            break;
        }
    }
    EXPECT_FALSE(all_equal);
}

TEST(NonlinearModelTest, InsufficientInput) {
    Params prm;
    std::vector<double> input(prm.steps - 2, 1.0);
    EXPECT_THROW(nonlin_model(prm, input), std::invalid_argument);
}
