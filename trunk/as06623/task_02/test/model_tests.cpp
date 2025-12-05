#include <gtest/gtest.h>
#include <vector>
#include "model.h"

TEST(SimulateLinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = simulateLinear(u);
    EXPECT_EQ(result.size(), iterationsCount);
}

TEST(SimulateNonlinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = simulateNonlinear(u);
    EXPECT_EQ(result.size(), iterationsCount);
}

TEST(SimulateLinearTest, ValuesAreCorrect) {
    double u = 5.0;
    std::vector<double> expected(iterationsCount);
    expected[0] = initialTemperature;

    for (int i = 0; i < iterationsCount - 1; ++i) {
        expected[i + 1] = coeffA * expected[i] + coeffB * u;
    }

    std::vector<double> result = simulateLinear(u);
    ASSERT_EQ(result.size(), expected.size());

    for (int i = 0; i < iterationsCount; ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-6);
    }
}
