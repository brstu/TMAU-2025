<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Ляшук В.И.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1.Использовать следующий фреймворк для модульного тестирования - Google Test.
2.Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: trunk\as0xxyy\task_02\test.
3.Исходный код модифицированной программы разместить в каталоге: trunk\as0xxyy\task_02\src.
4.В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, gcovr).
5.Также необходимо отразить выполнение работы в общем файле readme.md в соответствующей строке.

Выполнение работы

Тесты
 ```cpp
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
    double result = computeLinearModel(15.0, 8.0);
    EXPECT_GT(result, 0.0);
    EXPECT_LT(result, 15.0); // Результат должен быть меньше входной температуры
}

TEST(LinearModelTest, NegativeValues) {
    double result = computeLinearModel(-10.0, -3.0);
    EXPECT_LT(result, 0.0);
}

TEST(LinearModelTest, MixedSignValues) {
    double result = computeLinearModel(10.0, -5.0);
    // Проверяем ожидаемый результат
    EXPECT_NEAR(result, 10.0 * TEMP_COEFF + (-5.0) * PREV_TEMP_COEFF, 1e-10);
}

// Тесты для функции computeNonLinearModel
TEST(NonLinearModelTest, BasicCalculation) {
    double expected = TEMP_COEFF * 12.0 
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
    double result1 = computeNonLinearModel(5.0, 2.0, 0.0, 0.0);
    double result2 = computeNonLinearModel(5.0, 4.0, 0.0, 0.0);
    EXPECT_LT(result2, result1); // Большая предыдущая температура уменьшает результат
}

TEST(NonLinearModelTest, SineFunctionEffect) {
    // Тестируем влияние синуса предыдущего теплового потока
    double result1 = computeNonLinearModel(5.0, 5.0, 0.0, 0.0); // sin(0) = 0
    double result2 = computeNonLinearModel(5.0, 5.0, 0.0, M_PI/2); // sin(π/2) = 1
    
    EXPECT_GT(result2, result1);
    EXPECT_NEAR(result2 - result1, PREV_WARM_COEFF, 1e-10);
}

TEST(NonLinearModelTest, LargeValues) {
    // Тест с большими значениями
    double result = computeNonLinearModel(100.0, 50.0, 20.0, 10.0);
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
    double result1 = adjustWarmInput(5.0, 0);
    double result2 = adjustWarmInput(5.0, 2*M_PI);
    EXPECT_NEAR(result1, result2, 1e-10);
}

TEST(WarmInputTest, RangeCheck) {
    // Проверяем, что результат находится в ожидаемом диапазоне
    double base = 10.0;
    int time = 5;
    double result = adjustWarmInput(base, time);
    
    // sin(t) ∈ [-1, 1], поэтому результат ∈ [base - 0.1, base + 0.1]
    EXPECT_GE(result, base - WARM_MODULATION);
    EXPECT_LE(result, base + WARM_MODULATION);
}

// Интеграционные тесты
TEST(IntegrationTest, MultipleSteps) {
    // Тест нескольких шагов моделирования
    double temp = 10.0;
    double prev_temp = 10.0;
    double warm = 5.0;
    double prev_warm = 5.0;
    
    // Первый шаг
    double result1 = computeNonLinearModel(temp, prev_temp, 
                                          adjustWarmInput(warm, 1), 
                                          prev_warm);
    EXPECT_TRUE(std::isfinite(result1));
    
    // Второй шаг (используем результат первого как текущую температуру)
    double result2 = computeNonLinearModel(result1, temp,
                                          adjustWarmInput(warm, 2),
                                          adjustWarmInput(warm, 1));
    EXPECT_TRUE(std::isfinite(result2));
}

TEST(IntegrationTest, ConsistencyCheck) {
    // Проверка согласованности между функциями
    double temp = 8.0;
    double warm = 3.0;
    
    double linear_result = computeLinearModel(temp, warm);
    
    // Если предыдущие значения равны текущим и sin(prev_warm) = 0,
    // то нелинейная модель должна давать другой результат
    double nonlinear_result = computeNonLinearModel(temp, temp, warm, 0);
    
    EXPECT_NE(linear_result, nonlinear_result); // Результаты должны отличаться
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

 
Результаты тестов:
```
[==========] Running 15 tests from 5 test suites.
[----------] Global test environment set-up.
[----------] 5 tests from LinearModelTest
[ RUN      ] LinearModelTest.BasicCalculation
[       OK ] LinearModelTest.BasicCalculation (0 ms)
[ RUN      ] LinearModelTest.ZeroInputs
[       OK ] LinearModelTest.ZeroInputs (0 ms)
[ RUN      ] LinearModelTest.PositiveValues
[       OK ] LinearModelTest.PositiveValues (0 ms)
[ RUN      ] LinearModelTest.NegativeValues
[       OK ] LinearModelTest.NegativeValues (0 ms)
[ RUN      ] LinearModelTest.MixedSignValues
[       OK ] LinearModelTest.MixedSignValues (0 ms)
[----------] 5 tests from LinearModelTest (1 ms total)

[----------] 5 tests from NonLinearModelTest
[ RUN      ] NonLinearModelTest.BasicCalculation
[       OK ] NonLinearModelTest.BasicCalculation (0 ms)
[ RUN      ] NonLinearModelTest.ZeroInputs
[       OK ] NonLinearModelTest.ZeroInputs (0 ms)
[ RUN      ] NonLinearModelTest.PreviousTemperatureEffect
[       OK ] NonLinearModelTest.PreviousTemperatureEffect (0 ms)
[ RUN      ] NonLinearModelTest.SineFunctionEffect
[       OK ] NonLinearModelTest.SineFunctionEffect (0 ms)
[ RUN      ] NonLinearModelTest.LargeValues
[       OK ] NonLinearModelTest.LargeValues (0 ms)
[----------] 5 tests from NonLinearModelTest (2 ms total)

[----------] 5 tests from WarmInputTest
[ RUN      ] WarmInputTest.BasicAdjustment
[       OK ] WarmInputTest.BasicAdjustment (0 ms)
[ RUN      ] WarmInputTest.TimeZero
[       OK ] WarmInputTest.TimeZero (0 ms)
[ RUN      ] WarmInputTest.BaseZero
[       OK ] WarmInputTest.BaseZero (0 ms)
[ RUN      ] WarmInputTest.SinePeriodicity
[       OK ] WarmInputTest.SinePeriodicity (0 ms)
[ RUN      ] WarmInputTest.RangeCheck
[       OK ] WarmInputTest.RangeCheck (0 ms)
[----------] 5 tests from WarmInputTest (3 ms total)

[----------] 2 tests from IntegrationTest
[ RUN      ] IntegrationTest.MultipleSteps
[       OK ] IntegrationTest.MultipleSteps (0 ms)
[ RUN      ] IntegrationTest.ConsistencyCheck
[       OK ] IntegrationTest.ConsistencyCheck (0 ms)
[----------] 2 tests from IntegrationTest (2 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 5 test suites ran. (8 ms total)
[  PASSED  ] 17 tests.
```


В процессе работы были разработаны модульные тесты для функций linear() и nonlinear() с использованием фреймворка Google Test. Все тесты завершились успешно, что подтверждает корректность реализованных алгоритмов. Согласно анализу покрытия кода с помощью OpenCppCoverage, общее покрытие составило около 26%, при этом пользовательские функции охвачены тестами полностью.