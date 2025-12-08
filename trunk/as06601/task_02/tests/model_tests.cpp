#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

TEST(LinearModelTest, ZeroInputs) {
    EXPECT_DOUBLE_EQ(linearModel(0.0, 0.0, 0.8, 0.15), 0.0);
}

TEST(LinearModelTest, BasicCase) {
    double r = linearModel(1.0, 1.0, 0.8, 0.15);
    EXPECT_NEAR(r, 0.95, 1e-12);
}

TEST(LinearModelTest, NegativeValues) {
    double r = linearModel(-2.0, -3.0, 0.8, 0.15);
    EXPECT_NEAR(r, -1.6 - 0.45, 1e-12);
}


// ========= НЕЛИНЕЙНАЯ МОДЕЛЬ =========

TEST(NonlinearModelTest, ZeroInputs) {
    double r = nonlinearModel(0.0, 0.0, 0.0, 0.0,
                              0.8, 0.15, 0.05);
    EXPECT_DOUBLE_EQ(r, 0.0);
}

TEST(NonlinearModelTest, BasicCase) {
    double r = nonlinearModel(0.8, 0.15, 0.15, 1.0,
                              1.0, 1.0, 1.0);
    double expected = 0.8 * 1.0 - 0.15 * 1.0 * 1.0 + 0.15 * 1.0 + 1.0 * sin(1.0);
    EXPECT_NEAR(r, expected, 1e-12);
}

TEST(NonlinearModelTest, NonlinearEffect) {
    double r1 = nonlinearModel(1.0, 1.0, 0.0, 0.0, 0.8, 0.15, 1.0);
    double r2 = nonlinearModel(1.0, 2.0, 0.0, 0.0, 0.8, 0.15, 1.0);
    EXPECT_LT(r2, r1);
}

TEST(NonlinearModelTest, SinTermAffectsOutput) {
    double r = nonlinearModel(1.0, 0.0, 0.0, 0.05,
                              0.0, 0.0, M_PI/2); // sin = 1
    EXPECT_NEAR(r, 0.05, 1e-12);
}