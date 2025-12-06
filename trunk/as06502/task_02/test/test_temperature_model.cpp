#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include <vector>
#include "temperature_model.h"

class TemperatureModelTest : public ::testing::Test {
private:
    std::vector<double> testInputs;
    double initialTemp;

protected:
    void SetUp() override {
        testInputs = {15.0, 16.5, 18.0};
        initialTemp = 20.0;
    }
    
    const std::vector<double>& getTestInputs() const { return testInputs; }
    double getInitialTemp() const { return initialTemp; }
};

TEST_F(TemperatureModelTest, LinearModelBasicCalculation) {
    auto result = TemperatureModel::calcLinear(20.0, 15.0);
    EXPECT_NEAR(result, (0.2 * 20.0) + (0.02 * 15.0), 0.001);
}

TEST_F(TemperatureModelTest, LinearModelZeroInput) {
    auto result = TemperatureModel::calcLinear(0.0, 0.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(TemperatureModelTest, LinearModelSequence) {
    std::vector<double> results;
    TemperatureModel::calculateLinearModel(getInitialTemp(), getTestInputs(), results);
    
    auto expected1 = (0.2 * 20.0) + (0.02 * 15.0);
    EXPECT_NEAR(results[0], expected1, 0.001);
    
    auto expected2 = (0.2 * expected1) + (0.02 * 16.5);
    EXPECT_NEAR(results[1], expected2, 0.001);
}

TEST_F(TemperatureModelTest, NonlinearModelBasicCalculation) {
    auto result = TemperatureModel::calcNonlinear(20.0, 20.0, 15.0, 14.0);
    
    auto expected = (0.2 * 20.0) - (0.02 * 20.0 * 20.0) + 
                   (0.03 * 15.0) + (0.04 * sin(14.0));
    EXPECT_NEAR(result, expected, 0.001);
}

TEST_F(TemperatureModelTest, NonlinearModelSequence) {
    std::vector<double> results;
    std::vector<double> localInputs = {10.0, 12.0, 14.0};
    
    TemperatureModel::calculateNonlinearModel(getInitialTemp(), localInputs, results);
    
    EXPECT_DOUBLE_EQ(results[0], getInitialTemp());
    EXPECT_TRUE(results[1] != getInitialTemp());
}

TEST_F(TemperatureModelTest, NonlinearModelWithExtremeValues) {
    auto result = TemperatureModel::calcNonlinear(100.0, 100.0, 50.0, 50.0);
    EXPECT_FALSE(std::isnan(result));
    EXPECT_FALSE(std::isinf(result));
}

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
    EXPECT_FALSE(TemperatureModel::validateInput(-101.0)); 
    EXPECT_FALSE(TemperatureModel::validateInput(1001.0));
}

TEST_F(TemperatureModelTest, InputArrayValidation) {
    std::vector<double> validInputs = {10.0, 20.0, 30.0};
    std::vector<double> invalidInputs = {10.0, NAN, 30.0};
    std::vector<double> emptyInputs;
    
    EXPECT_TRUE(TemperatureModel::validateInputArray(validInputs));
    EXPECT_FALSE(TemperatureModel::validateInputArray(invalidInputs));
    EXPECT_FALSE(TemperatureModel::validateInputArray(emptyInputs));
}

TEST_F(TemperatureModelTest, LinearModelInvalidInputThrows) {
    EXPECT_THROW(TemperatureModel::calcLinear(NAN, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcLinear(20.0, INFINITY), std::invalid_argument);
}

TEST_F(TemperatureModelTest, NonlinearModelInvalidInputThrows) {
    EXPECT_THROW(TemperatureModel::calcNonlinear(NAN, 20.0, 10.0, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcNonlinear(20.0, -101.0, 10.0, 10.0), std::invalid_argument);
}

TEST_F(TemperatureModelTest, ModelSequenceInvalidInputThrows) {
    std::vector<double> invalidInputs = {10.0, NAN, 30.0};
    std::vector<double> results;
    
    EXPECT_THROW(TemperatureModel::calculateLinearModel(20.0, invalidInputs, results), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calculateNonlinearModel(20.0, invalidInputs, results), std::invalid_argument);
}

TEST_F(TemperatureModelTest, NonlinearModelInsufficientStepsThrows) {
    std::vector<double> singleInput = {10.0};
    std::vector<double> results;
    
    EXPECT_THROW(TemperatureModel::calculateNonlinearModel(20.0, singleInput, results), std::invalid_argument);
}

TEST_F(TemperatureModelTest, ConstantsAreCorrect) {
    EXPECT_DOUBLE_EQ(TemperatureModel::A, 0.2);
    EXPECT_DOUBLE_EQ(TemperatureModel::B, 0.02);
    EXPECT_DOUBLE_EQ(TemperatureModel::C, 0.03);
    EXPECT_DOUBLE_EQ(TemperatureModel::D, 0.04);
}

TEST_F(TemperatureModelTest, BoundaryCases) {
    EXPECT_NO_THROW(TemperatureModel::calcLinear(1000.0, 1000.0));
    EXPECT_NO_THROW(TemperatureModel::calcLinear(-100.0, -100.0));
    
    EXPECT_THROW(TemperatureModel::calcLinear(1001.0, 10.0), std::invalid_argument);
    EXPECT_THROW(TemperatureModel::calcLinear(10.0, -101.0), std::invalid_argument);
}

TEST_F(TemperatureModelTest, MathematicalProperties) {
    auto result1 = TemperatureModel::calcLinear(10.0, 5.0);
    auto result2 = TemperatureModel::calcLinear(20.0, 10.0);
    
    EXPECT_NEAR(result2, 2 * result1, 1.0);
}

TEST_F(TemperatureModelTest, PerformanceNoCrash) {
    bool allPassed = true;
    
    for (auto i = 0; i < 100; ++i) {
        auto temp = static_cast<double>(i);
        auto input = static_cast<double>(i * 2);
        
        try {
            TemperatureModel::calcLinear(temp, input);
        } catch (const std::invalid_argument&) {
            allPassed = false;
        }
    }
    
    EXPECT_TRUE(allPassed);
}