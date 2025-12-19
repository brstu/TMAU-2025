// test_temperature_model.cpp
#include <gtest/gtest.h>
#include "temperature_model.h"
#include <cmath>
#include <vector>

// Тесты для линейной модели
TEST(LinearModelTest, SimulateLinear) {
    LinearParams params{0.8, 0.15};
    
    // Проверка базового случая
    double result = simulate_linear(20.0, 10.0, params);
    EXPECT_DOUBLE_EQ(result, 0.8 * 20.0 + 0.15 * 10.0);
    
    // Проверка с нулевыми значениями
    result = simulate_linear(0.0, 0.0, params);
    EXPECT_DOUBLE_EQ(result, 0.0);
    
    // Проверка с отрицательными значениями
    result = simulate_linear(-10.0, -5.0, params);
    EXPECT_DOUBLE_EQ(result, 0.8 * (-10.0) + 0.15 * (-5.0));
}

TEST(LinearModelTest, StabilityCheck) {
    LinearParams params{0.8, 0.15};
    
    // Проверка многократного применения
    double temp = 0.0;
    for (int i = 0; i < 10; ++i) {
        temp = simulate_linear(temp, 1.0, params);
    }
    
    // Проверка что температура не уходит в бесконечность
    EXPECT_TRUE(std::isfinite(temp));
    EXPECT_LT(std::abs(temp), 1000.0); // Реалистичные пределы
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, SimulateNonlinear) {
    NonlinearParams params{0.8, 0.15, 0.05, 0.1};
    
    double result = simulate_nonlinear(20.0, 15.0, 10.0, 5.0, params);
    double expected = 0.8 * 20.0 - 0.15 * 15.0 * 15.0 + 0.05 * 10.0 + 0.1 * std::sin(5.0);
    EXPECT_NEAR(result, expected, 1e-10);
    
    // Проверка граничных случаев
    result = simulate_nonlinear(0.0, 0.0, 0.0, 0.0, params);
    expected = 0.8 * 0.0 - 0.15 * 0.0 + 0.05 * 0.0 + 0.1 * std::sin(0.0);
    EXPECT_DOUBLE_EQ(result, expected);
}


// Интеграционные тесты
TEST(IntegrationTest, RunSimulationConsistency) {
    LinearParams lin_params{0.8, 0.15};
    NonlinearParams nonlin_params{0.8, 0.15, 0.05, 0.1};
    
    const int steps = 10;
    std::vector<double> heat_input(steps, 1.0);
    std::vector<double> temp_lin(steps, 0.0);
    std::vector<double> temp_nonlin(steps, 0.0);
    
    // Выполняем симуляцию вручную для проверки
    for (int i = 1; i < steps; ++i) {
        temp_lin[i] = simulate_linear(temp_lin[i - 1], heat_input[i - 1], lin_params);
        
        if (i > 1) {
            temp_nonlin[i] = simulate_nonlinear(temp_nonlin[i - 1], temp_nonlin[i - 2],
                                                heat_input[i - 1], heat_input[i - 2], nonlin_params);
        } else {
            LinearParams temp_lin_params{nonlin_params.alpha, lin_params.beta};
            temp_nonlin[i] = simulate_linear(temp_nonlin[i - 1], heat_input[i - 1], temp_lin_params);
        }
    }
    
    // Проверка что температуры не NaN
    for (int i = 0; i < steps; ++i) {
        EXPECT_FALSE(std::isnan(temp_lin[i]));
        EXPECT_FALSE(std::isnan(temp_nonlin[i]));
    }
    
    // Проверка что массив был заполнен
    EXPECT_NE(temp_lin[0], temp_lin[steps-1]);
    EXPECT_NE(temp_nonlin[0], temp_nonlin[steps-1]);
}

TEST(ParameterTest, ValidParameterRanges) {
    // Проверка что параметры в разумных пределах
    LinearParams lin{0.8, 0.15};
    NonlinearParams nonlin{0.8, 0.15, 0.05, 0.1};
    
    EXPECT_TRUE(lin.alpha >= 0 && lin.alpha <= 1.0);
    EXPECT_TRUE(lin.beta >= 0 && lin.beta <= 1.0);
    EXPECT_TRUE(nonlin.alpha >= 0 && nonlin.alpha <= 1.0);
    EXPECT_TRUE(nonlin.beta >= 0 && nonlin.beta <= 1.0);
    EXPECT_TRUE(nonlin.gamma >= 0 && nonlin.gamma <= 1.0);
    EXPECT_TRUE(nonlin.delta >= 0 && nonlin.delta <= 1.0);
}

// Тест на ошибки
TEST(ErrorHandlingTest, InvalidValues) {
    LinearParams lin{0.8, 0.15};
    NonlinearParams nonlin{0.8, 0.15, 0.05, 0.1};
    
    // Проверка с большими значениями
    double result = simulate_linear(1e6, 1e6, lin);
    EXPECT_TRUE(std::isfinite(result));
    
    result = simulate_nonlinear(1e6, 1e6, 1e6, 1e6, nonlin);
    EXPECT_TRUE(std::isfinite(result));
    
    // Проверка с бесконечностью
    result = simulate_linear(std::numeric_limits<double>::infinity(), 0.0, lin);
    EXPECT_TRUE(std::isinf(result));
}
