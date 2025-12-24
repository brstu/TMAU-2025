#include <gtest/gtest.h>
#include "../src/temp_model.h"
#include <cmath>


TEST(LinModelTest, ZeroInZeroStay)
{
    Lin p{0.8, 0.2};
    
    double exp = p.a * 0.0 + p.b * 0.0;
    double actual = iter_lin(0.0, 0.0, p);

    EXPECT_DOUBLE_EQ(actual, exp);
}

TEST(LinModelTest, SimpleIter)
{
    Lin p{0.8, 0.2};

    double exp = p.a * 10.0 + p.b * 5.0;
    double actual = iter_lin(10.0, 5.0, p);

    EXPECT_DOUBLE_EQ(actual, exp);
}

TEST(LinModelTest, NegativeVal)
{
    Lin p{0.5, 0.5};

    double exp = p.a * (-4.0) + p.b * (-2.0);
    double actual = iter_lin(-4.0, -2.0, p);

    EXPECT_DOUBLE_EQ(actual, exp);
}


TEST(NonlinModelTest, ZeroAll)
{
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double exp = 0.0;
    double actual = iter_nonlin(0, 0, 0, 0, p);

    EXPECT_DOUBLE_EQ(actual, exp);
}

TEST(NonlinModelTest, NoSinEff)
{
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double exp = p.a * 10.0 - p.b * (2.0 * 2.0) + p.c * 1.0 + p.d * std::sin(0.0);
    double actual = iter_nonlin(10.0, 2.0, 1.0, 0.0, p);

    EXPECT_NEAR(actual, exp, 1e-6);
}

TEST(NonlinModelTest, WithSinEff)
{
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double exp = p.a * 5.0 - p.b * (1.0 * 1.0) + p.c * 2.0 + p.d * std::sin(M_PI / 2);
    double actual = iter_nonlin(5.0, 1.0, 2.0, M_PI/2, p);

    EXPECT_NEAR(actual, exp, 1e-9);
}
