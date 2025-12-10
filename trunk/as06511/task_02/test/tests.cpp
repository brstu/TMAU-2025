#include <gtest/gtest.h>
#include "../src/temp_model.h"
#include <cmath>


TEST(LinearModelTest, ZeroInputZeroState) {
    Lin p{0.8, 0.2};
    
    double expected = p.a * 0.0 + p.b * 0.0;
    double result = step_lin(0.0, 0.0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(LinearModelTest, SimpleStep) {
    Lin p{0.8, 0.2};

    double expected = p.a * 10.0 + p.b * 5.0;
    double result = step_lin(10.0, 5.0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(LinearModelTest, NegativeValues) {
    Lin p{0.5, 0.5};

    double expected = p.a * (-4.0) + p.b * (-2.0);
    double result = step_lin(-4.0, -2.0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}


TEST(NonlinearModelTest, ZeroEverything) {
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double expected = 0.0;
    double result = step_nonlin(0, 0, 0, 0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, NoSinEffect) {
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double expected = p.a * 10.0 - p.b * (2.0 * 2.0) + p.c * 1.0 + p.d * std::sin(0.0);
    double result = step_nonlin(10.0, 2.0, 1.0, 0.0, p);

    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithSinEffect) {
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double expected = p.a * 5.0 - p.b * (1.0 * 1.0) + p.c * 2.0 + p.d * std::sin(M_PI / 2);
    double result = step_nonlin(5.0, 1.0, 2.0, M_PI/2, p);

    EXPECT_NEAR(result, expected, 1e-9);
}
