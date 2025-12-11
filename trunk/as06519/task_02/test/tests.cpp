#include <gtest/gtest.h>
#include "../src/temp_model.h"
#include <cmath>

TEST(LinearModel, Basic) {
    LinParams p{0.75, 0.18};
    EXPECT_DOUBLE_EQ(linear_model(2.0, 1.0, p), 0.75*2.0 + 0.18*1.0);
}

TEST(LinearModel, ZeroInput) {
    LinParams p{0.5, 0.3};
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, p), 0.0);
}

TEST(LinearModel, NegativeInput) {
    LinParams p{0.5, 0.3};
    EXPECT_DOUBLE_EQ(linear_model(-2.0, -1.0, p), -1.0 - 0.3);
}

TEST(NonlinearModel, Basic) {
    NonlinParams p{0.75, 0.18, 0.07, 0.12};
    double expected = p.a*2 - p.b*1*1 + p.c*1 + p.d*sin(0);
    EXPECT_NEAR(nonlinear_model(2, 1, 1, 0, p), expected, 1e-9);
}

TEST(NonlinearModel, ZeroValues) {
    NonlinParams p{0.75, 0.18, 0.07, 0.12};
    EXPECT_DOUBLE_EQ(nonlinear_model(0, 0, 0, 0, p), 0.0);
}

TEST(NonlinearModel, Finite) {
    NonlinParams p{0.75, 0.18, 0.07, 0.12};
    double r = nonlinear_model(10, 5, 2, 1, p);
    EXPECT_TRUE(std::isfinite(r));
}
