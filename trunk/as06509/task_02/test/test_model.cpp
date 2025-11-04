#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

TEST(LinearModelTest, BaseValues) {
    Constants con;
    std::vector<double> u(10, 4.0);
    auto y = linear(con, u);

    EXPECT_EQ(y.size(), con.n + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
}

TEST(LinearModelTest, ZeroInput) {
    Constants con;
    std::vector<double> u(10, 0.0);
    auto y = linear(con, u);

    EXPECT_NEAR(y[1], 25.0 * con.a, 1e-6);
    EXPECT_NEAR(y[2], 25.0 * con.a * con.a, 1e-6);
}

TEST(LinearModelTest, InsufficientInput) {
    Constants con;
    std::vector<double> u(con.n - 1, 1.0); 
    EXPECT_THROW(linear(con, u), std::invalid_argument);
}


TEST(NonlinearModelTest, StartValues) {
    Constants con;
    std::vector<double> u(10, 4.0);
    auto y = nonlinear(con, u);

    EXPECT_EQ(y.size(), con.n + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
    EXPECT_DOUBLE_EQ(y[1], 25.0);
}

TEST(NonlinearModelTest, InputInfluence) {
    Constants con;
    std::vector<double> u1(10, 4.0);
    std::vector<double> u2(10, 8.0);

    auto y1 = nonlinear(con, u1);
    auto y2 = nonlinear(con, u2);

    EXPECT_GT(y2.back(), y1.back());
}

TEST(NonlinearModelTest, OutputChanges) {
    Constants con;
    std::vector<double> u = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto y = nonlinear(con, u);

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
    Constants con;
    std::vector<double> u(con.n - 2, 1.0); 
    EXPECT_THROW(nonlinear(con, u), std::invalid_argument);
}
