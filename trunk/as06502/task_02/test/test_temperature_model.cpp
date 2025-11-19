#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include "temperature_model.h"

class TemperatureModelTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Общие тестовые данные
        testInputs[0] = 15.0;
        testInputs[1] = 16.5;
        testInputs[2] = 18.0;
        initialTemp = 20.0;
    }
    
    double testInputs[3];
    double initialTemp;
};

// Тесты для линейной модели
TEST_F(TemperatureModelTest, LinearModelBasicCalculation) {
    double result = TemperatureModel::calcLinear(20.0, 15.0);
    EXPECT_NEAR(result, (0.2 * 20.0) + (0.02 * 15.0), 0.001);
}

TEST_F(TemperatureModelTest, LinearModelZeroInput) {
    double result = TemperatureModel::calcLinear(0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(TemperatureModelTest, LinearModelSequence) {
    double results[3];
    TemperatureModel::calculateLinearModel(initialTemp, testInputs, 3, results);
    
    // Проверяем первое значение
    double expected1 = (0.2 * 20.0) + (0.02 * 15.0);
    EXPECT_NEAR(results[0], expected1, 0.001);
    
    // Проверяем второе значение
    double expected2 = (0.2 * expected1) + (0.02 * 16.5);
    EXPECT_NEAR(results[1], expected2, 0.001);
}

// Тесты для нелинейной модели
TEST_F(TemperatureModelTest, NonlinearModelBasicCalculation) {
    double result = TemperatureModel::calcNonlinear(20.0, 20.0, 15.0, 14.0);
    
    double expected = (0.2 * 20.0) - (0.02 * 20.0 * 20.0) + 
                     (0.03 * 15.0) + (0.04 * sin(14.0));
    EXPECT_NEAR(result, expected, 0.001);
}

TEST_F(TemperatureModelTest, NonlinearModelSequence) {
    double results[3];
    double localInputs[3] = {10.0, 12.0, 14.0};
    
    TemperatureModel::calculateNonlinearModel(initialTemp, localInputs, 3, results);
    
    // Первое значение должно быть начальной температурой
    EXPECT_DOUBLE_EQ(results[0], initialTemp);
    
    // Второе значение рассчитывается
    EXPECT_TRUE(results[1] != initialTemp);
}

TEST_F(TemperatureModelTest, NonlinearModelWithExtremeValues) {
    // Проверяем работу с граничными значениями
    double result = TemperatureModel::calcNonlinear(100.0, 100.0, 50.0, 50.0);
    EXPECT_FALSE(std::isnan(result));
    EXPECT_FALSE(std::isinf(result));
}

// Тесты валидации входных данных
TEST_F(TemperatureModelTest, InputValidationValid) {
    EXPECT_TRUE(TemperatureModel::validateInput(20.0));
    EXPECT_TRUE(TemperatureModel::validateInput(0.0));
    EXPECT_TRUE(TemperatureModel::validateInput(-10.0));
    EXPECT_TRUE(TemperatureModel::validateInput(100.0));
}

TEST_F(TemperatureModelTest, InputValidationInvalid) {
    EXPECT_FALSE(TemperatureModel::validateInput(NAN));
    EXPECT_FALSE(TemperatureModel::validateInput(INFINITY));
    EXPECT_FALSE(TemperatureModel::validateInput(-INFINITY));
    EXPECT_FALSE(TemperatureModel::validateInput(-101.0));  // Ниже допустимого
    EXPECT_FALSE(TemperatureModel::validateInput(1001.0));  // Выше допустимого
}

TEST_F(TemperatureModelTest, InputArrayValidation) {
    double validInputs[3] = {10.0, 20.0, 30.0};
    double invalidInputs[3] = {10.0, NAN, 30.0};
    
    EXPECT_TRUE(TemperatureModel::validateInputArray(validInputs, 3));
    EXPECT_FALSE(TemperatureModel::validateInputArray(invalidInputs, 3));
    EXPECT_FALSE(TemperatureModel::validateInputArray(validInputs, 0));  // Пустой массив
}

// Тесты обработки ошибок
TEST_F(TemperatureModelTest, LinearModelInvalidInputThrows) {
    EXPECT_THROW(TemperatureModel::calcLinear(NAN, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcLinear(20.0, INFINITY), std::invalid_argument);
}

TEST_F(TemperatureModelTest, NonlinearModelInvalidInputThrows) {
    EXPECT_THROW(TemperatureModel::calcNonlinear(NAN, 20.0, 10.0, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcNonlinear(20.0, -101.0, 10.0, 10.0), std::invalid_argument);
}

TEST_F(TemperatureModelTest, ModelSequenceInvalidInputThrows) {
    double invalidInputs[3] = {10.0, NAN, 30.0};
    double results[3];
    
    EXPECT_THROW(TemperatureModel::calculateLinearModel(20.0, invalidInputs, 3, results), 
                 std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calculateNonlinearModel(20.0, invalidInputs, 3, results), 
                 std::invalid_argument);
}

TEST_F(TemperatureModelTest, NonlinearModelInsufficientStepsThrows) {
    double singleInput[1] = {10.0};
    double results[1];
    
    EXPECT_THROW(TemperatureModel::calculateNonlinearModel(20.0, singleInput, 1, results), 
                 std::invalid_argument);
}

// Тесты на постоянные значения
TEST_F(TemperatureModelTest, ConstantsAreCorrect) {
    EXPECT_DOUBLE_EQ(TemperatureModel::A, 0.2);
    EXPECT_DOUBLE_EQ(TemperatureModel::B, 0.02);
    EXPECT_DOUBLE_EQ(TemperatureModel::C, 0.03);
    EXPECT_DOUBLE_EQ(TemperatureModel::D, 0.04);
    //EXPECT_EQ(TemperatureModel::STEPS, 10);
}

// Тесты на граничные случаи
TEST_F(TemperatureModelTest, BoundaryCases) {
    // Максимально допустимые значения
    EXPECT_NO_THROW(TemperatureModel::calcLinear(1000.0, 1000.0));
    EXPECT_NO_THROW(TemperatureModel::calcLinear(-100.0, -100.0));
    
    // За границами - должны быть исключения
    EXPECT_THROW(TemperatureModel::calcLinear(1001.0, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcLinear(10.0, -101.0), std::invalid_argument);
}

// Тесты на математическую корректность
TEST_F(TemperatureModelTest, MathematicalProperties) {
    // Линейная модель должна быть линейной
    double result1 = TemperatureModel::calcLinear(10.0, 5.0);
    double result2 = TemperatureModel::calcLinear(20.0, 10.0);
    
    // Проверяем линейность: result2 должен быть примерно равен 2 * result1
    // с учетом того что у нас есть член A * y
    EXPECT_NEAR(result2, 2 * result1, 1.0);
}

// Тесты производительности (проверка на отсутствие падений)
TEST_F(TemperatureModelTest, PerformanceNoCrash) {
    for (int i = 0; i < 100; ++i) {
        double temp = static_cast<double>(i);
        double input = static_cast<double>(i * 2);
        EXPECT_NO_THROW(TemperatureModel::calcLinear(temp, input));
    }
}