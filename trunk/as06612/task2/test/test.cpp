#include <gtest/gtest.h>
#include "func.h"
#include <cmath>
#include <limits>

// Тесты для функции computeLinearModel
TEST(LinearModelTest, BasicCalculation) {
    EXPECT_NEAR(computeLinearModel(10.0, 5.0), 
                TEMP_COEFF * 10.0 + PREV_TEMP_COEFF * 5.0, 
                1e-10);
}

TEST(LinearModelTest, ZeroInputs) {
    EXPECT_DOUBLE_EQ(computeLinearModel(0.0, 0.0), 0.0);
}

TEST(LinearModelTest, PositiveValues) {
    auto result = computeLinearModel(15.0, 8.0);
    EXPECT_GT(result, 0.0);
    EXPECT_LT(result, 15.0); // Результат должен быть меньше входной температуры
}

TEST(LinearModelTest, NegativeValues) {
    auto result = computeLinearModel(-10.0, -3.0);
    EXPECT_LT(result, 0.0);
}

TEST(LinearModelTest, MixedSignValues) {
    auto result = computeLinearModel(10.0, -5.0);
    // Проверяем ожидаемый результат
    EXPECT_NEAR(result, 10.0 * TEMP_COEFF + (-5.0) * PREV_TEMP_COEFF, 1e-10);
}

// Тесты для функции computeNonLinearModel
TEST(NonLinearModelTest, BasicCalculation) {
    auto expected = TEMP_COEFF * 12.0 
                    - PREV_TEMP_COEFF * std::pow(10.0, 2)
                    + WARM_COEFF * 4.0
                    + PREV_WARM_COEFF * std::sin(3.0);
    
    EXPECT_NEAR(computeNonLinearModel(12.0, 10.0, 4.0, 3.0),
                expected, 1e-10);
}

TEST(NonLinearModelTest, ZeroInputs) {
    EXPECT_DOUBLE_EQ(computeNonLinearModel(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonLinearModelTest, PreviousTemperatureEffect) {
    // Тестируем влияние квадрата предыдущей температуры
    auto result1 = computeNonLinearModel(5.0, 2.0, 0.0, 0.0);
    auto result2 = computeNonLinearModel(5.0, 4.0, 0.0, 0.0);
    EXPECT_LT(result2, result1); // Большая предыдущая температура уменьшает результат
}

TEST(NonLinearModelTest, SineFunctionEffect) {
    // Тестируем влияние синуса предыдущего теплового потока
    auto result1 = computeNonLinearModel(5.0, 5.0, 0.0, 0.0); // sin(0) = 0
    auto result2 = computeNonLinearModel(5.0, 5.0, 0.0, M_PI/2); // sin(π/2) = 1
    
    EXPECT_GT(result2, result1);
    EXPECT_NEAR(result2 - result1, PREV_WARM_COEFF, 1e-10);
}

TEST(NonLinearModelTest, LargeValues) {
    // Тест с большими значениями
    auto result = computeNonLinearModel(100.0, 50.0, 20.0, 10.0);
    EXPECT_TRUE(std::isfinite(result)); // Результат должен быть конечным числом
}

// Тесты для функции adjustWarmInput
TEST(WarmInputTest, BasicAdjustment) {
    EXPECT_NEAR(adjustWarmInput(5.0, 2),
                5.0 + WARM_MODULATION * std::sin(2.0),
                1e-10);
}

TEST(WarmInputTest, TimeZero) {
    EXPECT_DOUBLE_EQ(adjustWarmInput(3.0, 0), 3.0);
}

TEST(WarmInputTest, BaseZero) {
    EXPECT_NEAR(adjustWarmInput(0.0, 1),
                WARM_MODULATION * std::sin(1.0),
                1e-10);
}

TEST(WarmInputTest, SinePeriodicity) {
    // Проверка периодичности синуса
    // Исправлено: приведение к целому числу через static_cast
    const auto period_steps = static_cast<int>(2 * M_PI);
    auto result1 = adjustWarmInput(5.0, 0);
    auto result2 = adjustWarmInput(5.0, period_steps);
    
    EXPECT_NEAR(result1, result2, 1e-10);
}

TEST(WarmInputTest, RangeCheck) {
    // Проверяем, что результат находится в ожидаемом диапазоне
    auto base = 10.0;
    auto time = 5;
    auto result = adjustWarmInput(base, time);
    
    // sin(t) ∈ [-1, 1], поэтому результат ∈ [base - 0.1, base + 0.1]
    EXPECT_GE(result, base - WARM_MODULATION);
    EXPECT_LE(result, base + WARM_MODULATION);
}

// Интеграционные тесты
TEST(IntegrationTest, MultipleSteps) {
    // Тест нескольких шагов моделирования
    auto temp = 10.0;
    auto prev_temp = 10.0;
    auto warm = 5.0;
    auto prev_warm = 5.0;
    
    // Первый шаг
    auto result1 = computeNonLinearModel(temp, prev_temp, 
                                         adjustWarmInput(warm, 1), 
                                         prev_warm);
    EXPECT_TRUE(std::isfinite(result1));
    
    // Второй шаг (используем результат первого как текущую температуру)
    auto result2 = computeNonLinearModel(result1, temp,
                                         adjustWarmInput(warm, 2),
                                         adjustWarmInput(warm, 1));
    EXPECT_TRUE(std::isfinite(result2));
}

TEST(IntegrationTest, ConsistencyCheck) {
    // Проверка согласованности между функциями
    auto temp = 8.0;
    auto warm = 3.0;
    
    auto linear_result = computeLinearModel(temp, warm);
    
    // Если предыдущие значения равны текущим и sin(prev_warm) = 0,
    // то нелинейная модель должна давать другой результат
    auto nonlinear_result = computeNonLinearModel(temp, temp, warm, 0);
    
    EXPECT_NE(linear_result, nonlinear_result); // Результаты должны отличаться
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}