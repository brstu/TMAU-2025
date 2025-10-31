#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "../src/model.h"

TEST(LinearModelTest, StepInput) {
    double a = 0.8, b = 0.2;
    double y = 0.0;
    double u = 1.0;

    for (int t = 0; t < 10; ++t) {
        y = compute_linear_model(y, u, a, b);
    }

    EXPECT_GT(y, 0.0);
}

TEST(NonlinearModelTest, SinusoidalInput) {
    double a = 0.8, b = 0.2, c = 0.1, d = 0.05;
    double y_prev = 0.0, y_curr = 0.0;
    double u_prev = 0.0, u_curr = 0.0;

    for (int t = 1; t < 10; ++t) {
        u_prev = u_curr;
        u_curr = sin(t * M_PI / 10);
        double y_next = compute_nonlinear_model(y_curr, y_prev, u_curr, u_prev, a, b, c, d);
        y_prev = y_curr;
        y_curr = y_next;
    }

    EXPECT_TRUE(abs(y_curr) < 10.0);
}
