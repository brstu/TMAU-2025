#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "../src/model.h"

TEST(LinearModelTest, StepInput) {
    double a = 0.8;
    double b = 0.2;
    double y = 0.0;
    double u = 1.0;

    for (int t = 0; t < 10; ++t) {
        y = compute_linear_model(y, u, a, b);
    }

    EXPECT_GT(y, 0.0);
}

TEST(LinearModelTest, ZeroInput) {
    double a = 0.5;
    double b = 0.5;
    double y = 1.0;
    double u = 0.0;

    for (int t = 0; t < 5; ++t) {
        y = compute_linear_model(y, u, a, b);
    }

    EXPECT_LT(y, 1.0);
}

TEST(LinearModelTest, NegativeCoefficients) {
    double a = -0.5;
    double b = -0.5;
    double y = 1.0;
    double u = 1.0;

    double result = compute_linear_model(y, u, a, b);
    EXPECT_LT(result, 0.0);
}

TEST(LinearModelTest, ImpulseResponse) {
    double a = 0.9;
    double b = 0.1;
    double y = 0.0;
    std::vector<double> u(10, 0.0);
    u[0] = 1.0;

    for (int t = 0; t < 10; ++t) {
        y = compute_linear_model(y, u[t], a, b);
    }

    EXPECT_GT(y, 0.0);
}

TEST(NonlinearModelTest, SinusoidalInput) {
    double a = 0.8;
    double b = 0.2;
    double c = 0.1;
    double d = 0.05;
    double y_prev = 0.0;
    double y_curr = 0.0;
    double u_prev = 0.0;
    double u_curr = 0.0;

    for (int t = 1; t < 10; ++t) {
        u_prev = u_curr;
        u_curr = sin(t * M_PI / 10);

        NonlinearParams p;
        p.y_curr = y_curr;
        p.y_prev = y_prev;
        p.u_curr = u_curr;
        p.u_prev = u_prev;
        p.a = a;
        p.b = b;
        p.c = c;
        p.d = d;

        double y_next = compute_nonlinear_model(p);
        y_prev = y_curr;
        y_curr = y_next;
    }

    EXPECT_TRUE(std::abs(y_curr) < 10.0);
}

TEST(NonlinearModelTest, StabilityCheck) {
    double a = 0.1;
    double b = 0.1;
    double c = 0.01;
    double d = 0.01;
    double y_prev = 0.0;
    double y_curr = 0.0;
    double u_prev = 0.0;
    double u_curr = 1.0;

    for (int t = 0; t < 50; ++t) {
        NonlinearParams p;
        p.y_curr = y_curr;
        p.y_prev = y_prev;
        p.u_curr = u_curr;
        p.u_prev = u_prev;
        p.a = a;
        p.b = b;
        p.c = c;
        p.d = d;

        double y_next = compute_nonlinear_model(p);
        y_prev = y_curr;
        y_curr = y_next;
    }

    EXPECT_LT(std::abs(y_curr), 5.0);
}

TEST(NonlinearModelTest, SymmetryCheck) {
    // Use named constants to clarify the intent of the test values.
    const double TEST_Y_CURR = 1.0; // Arbitrary current output value
    const double TEST_Y_PREV = 2.0; // Arbitrary previous output value
    const double TEST_U_CURR = 3.0; // Arbitrary current input value
    const double TEST_U_PREV = 4.0; // Arbitrary previous input value

    NonlinearParams p1;
    p1.y_curr = TEST_Y_CURR;
    p1.y_prev = TEST_Y_PREV;
    p1.u_curr = TEST_U_CURR;
    p1.u_prev = TEST_U_PREV;
    p1.a = 0.5;
    p1.b = 0.5;
    p1.c = 0.2;
    p1.d = 0.1;

    NonlinearParams p2 = p1;
    std::swap(p2.y_curr, p2.y_prev);
    std::swap(p2.u_curr, p2.u_prev);

    double y1 = compute_nonlinear_model(p1);
    double y2 = compute_nonlinear_model(p2);

    EXPECT_NE(y1, y2);
}

TEST(NonlinearModelTest, ParameterSensitivity) {
    NonlinearParams low;
    low.y_curr = 1.0;
    low.y_prev = 1.0;
    low.u_curr = 1.0;
    low.u_prev = 1.0;
    low.a = 0.1;
    low.b = 0.1;
    low.c = 0.1;
    low.d = 0.1;

    NonlinearParams high = low;
    high.a = 1.0;
    high.b = 1.0;
    high.c = 1.0;
    high.d = 1.0;

    double y_low = compute_nonlinear_model(low);
    double y_high = compute_nonlinear_model(high);

    EXPECT_LT(y_low, y_high);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
