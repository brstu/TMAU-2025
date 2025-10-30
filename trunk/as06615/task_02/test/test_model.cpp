#include <gtest/gtest.h>
#include <vector>
#include "../src/model.h"

// -------------------------
// Тесты для compute_derivative
// -------------------------

TEST(DerivativeTest, EmptyErrors) {
    std::vector<double> errors;
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.1), 0.0);
}

TEST(DerivativeTest, SingleErrorValue) {
    std::vector<double> errors = {1.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.1), 0.0);
}

TEST(DerivativeTest, ZeroDeltaTime) {
    std::vector<double> errors = {1.0, 2.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.0), 0.0);
}

TEST(DerivativeTest, PositiveDerivative) {
    std::vector<double> errors = {1.0, 2.5};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.5), 3.0);
}

TEST(DerivativeTest, NegativeDerivative) {
    std::vector<double> errors = {2.0, 1.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 1.0), -1.0);
}

TEST(DerivativeTest, ConstantError) {
    std::vector<double> errors = {2.0, 2.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 1.0), 0.0);
}

TEST(DerivativeTest, SmallDeltaTime) {
    std::vector<double> errors = {1.0, 1.5};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.0001), 5000.0);
}

TEST(DerivativeTest, LongErrorSequence) {
    std::vector<double> errors = {0.0, 0.5, 1.0, 1.5, 2.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.5), 1.0);
}

TEST(DerivativeTest, NearZeroDeltaTime) {
    std::vector<double> errors = {1.0, 2.0};
    double dt = std::numeric_limits<double>::epsilon() / 2;
    EXPECT_DOUBLE_EQ(compute_derivative(errors, dt), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
