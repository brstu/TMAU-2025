#include <gtest/gtest.h>
#include "../src/t_model.h"
#include <cmath>

// lin
TEST(LinearModel, ZeroInputZeroState) {
    ParamsLin p{0.77, 0.29};
    EXPECT_DOUBLE_EQ(model_linear(0.0, 0.0, p), 0.0);
}

TEST(LinearModel, BasicCalculation) {
    ParamsLin p{0.77, 0.29};
    double expected = 0.77 * 10.0 + 0.29 * 2.0;
    EXPECT_DOUBLE_EQ(model_linear(10.0, 2.0, p), expected);
}

TEST(LinearModel, NegativeValues) {
    ParamsLin p{0.5, 0.5};
    double expected = 0.5 * (-4.0) + 0.5 * (-6.0);
    EXPECT_DOUBLE_EQ(model_linear(-4.0, -6.0, p), expected);
}


// nonlin
TEST(NonlinearModel, ZeroAll) {
    ParamsNonlin p{0.86, 0.15, 0.10, 0.11};
    EXPECT_DOUBLE_EQ(model_nonlinear(0, 0, 0, 0, p), 0.0);
}

TEST(NonlinearModel, NoSinEffect) {
    ParamsNonlin p{0.86, 0.15, 0.10, 0.11};
    double y1 = 5.0, y2 = 1.0, u1 = 2.0, u2 = 0.0;
    double expected = 0.86 * y1 - 0.15 * (y2 * y2) + 0.10 * u1 + 0.11 * std::sin(0.0);
    EXPECT_NEAR(model_nonlinear(y1, y2, u1, u2, p), expected, 1e-9);
}

TEST(NonlinearModel, WithSinus) {
    ParamsNonlin p{0.86, 0.15, 0.10, 0.11};
    double u2 = M_PI / 2;
    double expected = 0.86 * 3.0 - 0.15 * (2.0 * 2.0) + 0.10 * 1.0 + 0.11 * std::sin(u2);

    EXPECT_NEAR(model_nonlinear(3.0, 2.0, 1.0, u2, p), expected, 1e-9);
}
