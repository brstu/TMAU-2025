#include <gtest/gtest.h>
#include "model.h"
#include <vector>
#include <cmath>

TEST(LinearModelTest, ZeroInput) {
    ModelParams params{10, 0.9, 0.02, 0.0, 0.0};
    std::vector<double> u(params.N + 1, 0.0);

    std::vector<double> y = linear_model(params, u, 0.0);

    for (double v : y) {
        EXPECT_NEAR(v, 0.0, 1e-9);
    }
}

TEST(LinearModelTest, Convergence) {
    ModelParams params{50, 0.9, 0.02, 0.0, 0.0};
    std::vector<double> u(params.N + 1, 1.0);

    std::vector<double> y = linear_model(params, u, 0.0);

    EXPECT_NEAR(y.back(), 0.2, 1e-2);
}

TEST(NonlinearModelTest, FiniteValues) {
    ModelParams params{30, 0.9, 0.02, 0.03, 0.1};
    std::vector<double> u(params.N + 1, 1.0);

    std::vector<double> y = nonlinear_model(params, u, 0.0, 0.0);

    for (double v : y) {
        EXPECT_TRUE(std::isfinite(v));
    }
}
