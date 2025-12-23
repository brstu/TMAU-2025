#include <gtest/gtest.h>
#include <vector>
#include "function.h"

TEST(LinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = linear(u);
    EXPECT_EQ(result.size(), iterations);
}

TEST(NonlinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = nonlinear(u);
    EXPECT_EQ(result.size(), iterations);
}

TEST(LinearTest, ValuesAreCorrect) {
    double u = 5.0;
    std::vector<double> expected(iterations);
    expected[0] = InpTemp;
    for (int i = 0; i < iterations - 1; ++i) {
        expected[i + 1] = a * expected[i] + b * u;
    }

    std::vector<double> result = linear(u);
    ASSERT_EQ(result.size(), expected.size());
    for (int i = 0; i < iterations; ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-6);
    }
}
