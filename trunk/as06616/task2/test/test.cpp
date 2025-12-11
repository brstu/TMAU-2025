#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

// Тесты для линейной модели
TEST(LinearModel, test_zero) {
    EXPECT_DOUBLE_EQ(linearmodel(0, 0), 0);
}

TEST(LinearModel, test_u0) {
    EXPECT_DOUBLE_EQ(linearmodel(18, 0), temperatureCoeff * 18);
}

TEST(LinearModel, test_y0) {
    EXPECT_DOUBLE_EQ(linearmodel(0, 5), prevTemperatureCoeff * 5);
}

TEST(LinearModel, test_default) {
    EXPECT_DOUBLE_EQ(linearmodel(18, 5), temperatureCoeff * 18 + prevTemperatureCoeff * 5);
}

// Тесты для нелинейной модели
TEST(NonLinearModel, test_zero) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(0, 0, 0, 0), 0);
}

TEST(NonLinearModel, test_u0) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(18, 18, 0, 0),
        temperatureCoeff * 18 - prevTemperatureCoeff * std::pow(18, 2));
}

TEST(NonLinearModel, test_y0) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(0, 0, 5, 5),
        warmCoeff * 5 + prevWarmCoeffSin * std::sin(5));
}

TEST(NonLinearModel, test_default) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(18, 18, 5, 5),
        temperatureCoeff * 18 - prevTemperatureCoeff * std::pow(18, 2) +
        warmCoeff * 5 + prevWarmCoeffSin * std::sin(5));
}

// Тесты для функции updateWarm
TEST(UpdateWarm, test_zero) {
    EXPECT_DOUBLE_EQ(updateWarm(0, 0), 0.1 * std::sin(0));
}

TEST(UpdateWarm, test_base_only) {
    EXPECT_DOUBLE_EQ(updateWarm(5, 0), 5 + 0.1 * std::sin(0));
}

TEST(UpdateWarm, test_time_only) {
    EXPECT_DOUBLE_EQ(updateWarm(0, 2), 0.1 * std::sin(2));
}

TEST(UpdateWarm, test_default) {
    EXPECT_DOUBLE_EQ(updateWarm(3, 1), 3 + 0.1 * std::sin(1));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
