#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <limits>
#include "../src/temperature_model.h"

class TemperatureModelTest : public ::testing::Test {
private:
    std::vector<double> testInputs;

protected:
    void SetUp() override {
        testInputs = {3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 9.0, 8.0};
    }
    
    const std::vector<double>& getTestInputs() const { return testInputs; }
    
    
    TemperatureModel createSilentModel(double a = 0.7, double b = 0.3, double c = 0.05, 
                                      double d = 0.01, double temp = 20.0, 
                                      const std::vector<double>& inputs = {}) const {
        if (inputs.empty()) {
            return TemperatureModel(a, b, c, d, temp, getTestInputs(), false);
        }
        return TemperatureModel(a, b, c, d, temp, inputs, false);
    }
    
    
    void CheckResultsValid(const std::vector<double>& results) const {
        for (const auto& value : results) {
            EXPECT_FALSE(std::isnan(value)) << "Found NaN in results";
            EXPECT_FALSE(std::isinf(value)) << "Found infinity in results";
        }
    }
};

TEST_F(TemperatureModelTest, ConstructorInitialization) {
    TemperatureModel model = createSilentModel();
    
    
    EXPECT_TRUE(model.getLinearResults().empty());
    EXPECT_TRUE(model.getNonlinearResults().empty());
}

TEST_F(TemperatureModelTest, RunLinearModelOutput) {
    TemperatureModel model = createSilentModel();
    model.runLinear();
    
    const auto& results = model.getLinearResults();
    
    
    EXPECT_EQ(results.size(), getTestInputs().size());
    
    
    CheckResultsValid(results);
    
    
    for (const auto& value : results) {
        EXPECT_GT(value, -10000.0);
        EXPECT_LT(value, 10000.0);
    }
}

TEST_F(TemperatureModelTest, RunNonlinearModelOutput) {
    TemperatureModel model = createSilentModel();
    model.runNonlinear();
    
    const auto& results = model.getNonlinearResults();
    
    EXPECT_EQ(results.size(), getTestInputs().size());
    CheckResultsValid(results);
    
    for (const auto& value : results) {
        EXPECT_GT(value, -10000.0);
        EXPECT_LT(value, 10000.0);
    }
}


TEST_F(TemperatureModelTest, SingleElementInput) {
    std::vector<double> singleInput = {5.0};
    TemperatureModel model = createSilentModel(0.7, 0.3, 0.05, 0.01, 20.0, singleInput);
    
    model.runLinear();
    model.runNonlinear();
    
    
    EXPECT_EQ(model.getLinearResults().size(), 1);
    EXPECT_EQ(model.getNonlinearResults().size(), 1);
    
    
    CheckResultsValid(model.getLinearResults());
    CheckResultsValid(model.getNonlinearResults());
}

TEST_F(TemperatureModelTest, MathematicalConsistencyLinear) {
    
    std::vector<double> inputs = {1.0, 2.0};
    TemperatureModel model = createSilentModel(0.5, 0.5, 0.0, 0.0, 1.0, inputs);
    
    model.runLinear();
    const auto& results = model.getLinearResults();
    
    
    
    ASSERT_EQ(results.size(), 2);
    EXPECT_NEAR(results[0], 1.0, 0.001); // из-за погрешностей дробных в двоичной форме
    EXPECT_NEAR(results[1], 1.5, 0.001);
}

TEST_F(TemperatureModelTest, MathematicalConsistencyNonlinear) {
    
    std::vector<double> inputs = {1.0};
    TemperatureModel model = createSilentModel(1.0, 0.0, 1.0, 0.0, 0.0, inputs); 
    
    model.runNonlinear();
    const auto& results = model.getNonlinearResults();
    
    
    
    ASSERT_EQ(results.size(), 1);
    EXPECT_NEAR(results[0], 1.0, 0.001);
}

TEST_F(TemperatureModelTest, CompareLinearAndNonlinear) {
    TemperatureModel model = createSilentModel();
    
    model.runLinear();
    model.runNonlinear();
    
    const auto& linearResults = model.getLinearResults();
    const auto& nonlinearResults = model.getNonlinearResults();
    
    ASSERT_EQ(linearResults.size(), nonlinearResults.size());
    
    
    bool resultsDiffer = false;
    for (size_t i = 0; i < linearResults.size(); ++i) {
        if (std::abs(linearResults[i] - nonlinearResults[i]) > 0.001) {
            resultsDiffer = true;
            break;
        }
    }
    EXPECT_TRUE(resultsDiffer) << "Linear and nonlinear models should produce different results";
}

TEST_F(TemperatureModelTest, RepeatedModelUsageConsistency) {
    TemperatureModel model = createSilentModel();
    
    
    model.runLinear();
    model.runNonlinear();
    const auto& firstLinear = model.getLinearResults();
    const auto& firstNonlinear = model.getNonlinearResults();
    
    
    model.runLinear();
    model.runNonlinear();
    const auto& secondLinear = model.getLinearResults();
    const auto& secondNonlinear = model.getNonlinearResults();
    
    
    ASSERT_EQ(firstLinear.size(), secondLinear.size());
    ASSERT_EQ(firstNonlinear.size(), secondNonlinear.size());
    
    for (size_t i = 0; i < firstLinear.size(); ++i) {
        EXPECT_NEAR(firstLinear[i], secondLinear[i], 0.001);
        EXPECT_NEAR(firstNonlinear[i], secondNonlinear[i], 0.001);
    }
}

TEST_F(TemperatureModelTest, SensitivityToCoefficients) {
    std::vector<double> inputs = {1.0, 2.0};
    
    
    TemperatureModel model1 = createSilentModel(0.7, 0.3, 0.05, 0.01, 10.0, inputs);
    TemperatureModel model2 = createSilentModel(0.8, 0.2, 0.05, 0.01, 10.0, inputs);
    
    model1.runLinear();
    model2.runLinear();
    
    const auto& results1 = model1.getLinearResults();
    const auto& results2 = model2.getLinearResults();
    
    ASSERT_EQ(results1.size(), results2.size());
    
    
    bool resultsDiffer = false;
    for (size_t i = 0; i < results1.size(); ++i) {
        if (std::abs(results1[i] - results2[i]) > 0.001) {
            resultsDiffer = true;
            break;
        }
    }
    EXPECT_TRUE(resultsDiffer) << "Results should differ with different coefficients";
}

TEST_F(TemperatureModelTest, BoundaryTemperatureValues) {
    std::vector<double> inputs = {1.0, 2.0};
    
    
    TemperatureModel model1 = createSilentModel(0.7, 0.3, 0.05, 0.01, 0.0, inputs);     
    TemperatureModel model2 = createSilentModel(0.7, 0.3, 0.05, 0.01, -100.0, inputs);  
    TemperatureModel model3 = createSilentModel(0.7, 0.3, 0.05, 0.01, 1000.0, inputs);  
    
    EXPECT_NO_THROW(model1.runLinear());
    EXPECT_NO_THROW(model2.runLinear());
    EXPECT_NO_THROW(model3.runLinear());
    
    EXPECT_NO_THROW(model1.runNonlinear());
    EXPECT_NO_THROW(model2.runNonlinear());
    EXPECT_NO_THROW(model3.runNonlinear());
    
    
    CheckResultsValid(model1.getLinearResults());
    CheckResultsValid(model2.getLinearResults());
    CheckResultsValid(model3.getLinearResults());
}

TEST_F(TemperatureModelTest, ExtremeCoefficientValues) {
    std::vector<double> inputs = {1.0, 2.0};
    
    
    TemperatureModel model1 = createSilentModel(0.0, 1.0, 0.0, 0.0, 10.0, inputs);  
    TemperatureModel model2 = createSilentModel(1.0, 0.0, 0.0, 0.0, 10.0, inputs);  
    TemperatureModel model3 = createSilentModel(2.0, 1.0, 0.0, 0.0, 10.0, inputs);  
    
    EXPECT_NO_THROW(model1.runLinear());
    EXPECT_NO_THROW(model2.runLinear());
    EXPECT_NO_THROW(model3.runLinear());
    
    
    CheckResultsValid(model1.getLinearResults());
    CheckResultsValid(model2.getLinearResults());
    CheckResultsValid(model3.getLinearResults());
}

TEST_F(TemperatureModelTest, PerformanceAndStability) {
    
    std::vector<double> largeInputs(100, 1.0); 
    
    TemperatureModel model = createSilentModel(0.7, 0.3, 0.05, 0.01, 20.0, largeInputs);
    
    for (int i = 0; i < 10; ++i) {
        // Combine the two EXPECT_NO_THROW calls into one to satisfy SonarQube rule
        EXPECT_NO_THROW({
            model.runLinear();
            model.runNonlinear();
        });
        
        const auto& linearResults = model.getLinearResults();
        const auto& nonlinearResults = model.getNonlinearResults();
        
        EXPECT_EQ(linearResults.size(), largeInputs.size());
        EXPECT_EQ(nonlinearResults.size(), largeInputs.size());
        
        CheckResultsValid(linearResults);
        CheckResultsValid(nonlinearResults);
    }
}