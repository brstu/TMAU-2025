#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

// Тесты для линейной модели
TEST(LinearModelTest, ZeroInitialValue) {
    EXPECT_NEAR(nextLinear(0.3, 0.3, 0.9, 0.0), 0.27, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(nextLinear(0.3, 0.3, 0.9, 1.0), 0.57, 1e-6);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_NEAR(nextLinear(0.5, 0.2, -1.0, 2.0), 0.8, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, ZeroInitialValues) {
    NonlinearParams params{0.1, 0.2, 0.4, 0.2};
    double result = nextNonlinear(params, 0.0, 0.0, 0.0); // u_prev, y, y_prev
    double expected = 0.1 * 0.0 - 0.2 * (0.0 * 0.0) + 0.4 * 0.0 + 0.2 * std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams params{0.1, 0.2, 0.4, 0.2};
    double result = nextNonlinear(params, 0.8, 0.5, 0.3); // u_prev, y, y_prev
    double expected = 0.1 * 0.5 - 0.2 * (0.3 * 0.3) + 0.4 * 0.8 + 0.2 * std::sin(0.8);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, ComplexCase) {
    NonlinearParams params{0.5, 0.1, 0.3, 0.4};
    double result = nextNonlinear(params, 1.0, 2.0, 1.5); // u_prev, y, y_prev
    double expected = 0.5 * 2.0 - 0.1 * (1.5 * 1.5) + 0.3 * 1.0 + 0.4 * std::sin(1.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

// Тесты для симуляции
TEST(SimulationTest, LinearSimulationRuns) {
    EXPECT_NO_THROW(simulateLinearVec(0.3, 0.3, 0.9, 5));
}

TEST(SimulationTest, NonlinearSimulationRuns) {
    EXPECT_NO_THROW(simulateNonlinearVec(0.1, 0.2, 0.4, 0.2, 0.8, 5));
}

TEST(SimulationTest, LinearSimulationValues) {
    auto result = simulateLinearVec(0.3, 0.3, 1.0, 3);
    EXPECT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.0, 1e-6);
    EXPECT_NEAR(result[1], 0.3, 1e-6);  // 0.3*0 + 0.3*1 = 0.3
    EXPECT_NEAR(result[2], 0.39, 1e-6); // 0.3*0.3 + 0.3*1 = 0.39
}

TEST(SimulationTest, NonlinearSimulationSize) {
    auto result = simulateNonlinearVec(0.1, 0.2, 0.4, 0.2, 0.8, 4);
    EXPECT_EQ(result.size(), 4);
}
