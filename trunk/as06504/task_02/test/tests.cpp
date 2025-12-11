#include <gtest/gtest.h>
#include "../src/model.h"

TEST(LinearModelTest, ZeroInput) {
    LinearCfg cfg{0.5, 0.3};
    EXPECT_DOUBLE_EQ(linearStep(0.0, 0.0, cfg), 0.0);
}

TEST(LinearModelTest, PositiveInput) {
    LinearCfg cfg{0.5, 0.3};
    EXPECT_NEAR(linearStep(2.0, 1.0, cfg), 1.3, 1e-6);
}

TEST(NonlinearModelTest, ZeroInput) {
    NonlinearCfg cfg{0.5, 0.2, 0.1, 0.05};
    EXPECT_DOUBLE_EQ(nonlinearStep(0.0, 0.0, 0.0, 0.0, cfg), 0.0);
}

TEST(NonlinearModelTest, MixedInput) {
    NonlinearCfg cfg{0.5, 0.2, 0.1, 0.05};
    double result = nonlinearStep(1.0, 2.0, 1.0, 0.5, cfg);
    double expected = 0.5 * 1.0 - 0.2 * 4.0 + 0.1 * 1.0 + 0.05 * std::sin(0.5);
    EXPECT_NEAR(result, expected, 1e-6);
}
