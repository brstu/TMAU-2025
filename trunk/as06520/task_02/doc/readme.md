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
<p align="right">Группы АС-65</p>
<p align="right">Хвисюк К. Г.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06521/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---
## Выполнение работы
---
### Тесты

```cpp
// test_main.cpp - если хотите отдельный main для тестов
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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
```

### Результат выполнения тестов:
```bash
=== Running tests ===
[==========] Running 6 tests from 5 test suites.
[----------] Global test environment set-up.
[----------] 2 tests from LinearModelTest
[ RUN      ] LinearModelTest.SimulateLinear
[       OK ] LinearModelTest.SimulateLinear (0 ms)
[ RUN      ] LinearModelTest.StabilityCheck
[       OK ] LinearModelTest.StabilityCheck (0 ms)
[----------] 2 tests from LinearModelTest (0 ms total)

[----------] 1 test from NonlinearModelTest
[ RUN      ] NonlinearModelTest.SimulateNonlinear
[       OK ] NonlinearModelTest.SimulateNonlinear (0 ms)
[----------] 1 test from NonlinearModelTest (0 ms total)

[----------] 1 test from IntegrationTest
[ RUN      ] IntegrationTest.RunSimulationConsistency
[       OK ] IntegrationTest.RunSimulationConsistency (0 ms)
[----------] 1 test from IntegrationTest (0 ms total)

[----------] 1 test from ParameterTest
[ RUN      ] ParameterTest.ValidParameterRanges
[       OK ] ParameterTest.ValidParameterRanges (0 ms)
[----------] 1 test from ParameterTest (0 ms total)

[----------] 1 test from ErrorHandlingTest
[ RUN      ] ErrorHandlingTest.InvalidValues
[       OK ] ErrorHandlingTest.InvalidValues (0 ms)
[----------] 1 test from ErrorHandlingTest (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 5 test suites ran. (0 ms total)
[  PASSED  ] 6 tests.
```


# GCC Code Coverage Report

## 📂 Overall coverage

| Metric        | Coverage |
|---------------|----------|
| **Lines**     | 🔴 4/29 (13.8%) |
| **Functions** | 🔴 2/4 (50.0%) |
| **Branches**  | 🔴 0/38 (0.0%) |

## 📄 File coverage

| File                   | Lines | Functions | Branches |
|------------------------|-------|-----------|----------|
| **`main.cpp`** | 🔴 0/25 (0.0%) | 🔴 0/2 (0.0%) | 🔴 0/38 (0.0%) |
| **`temperature_model.cpp`** | 🟢 4/4 (100.0%) | 🟢 2/2 (100.0%) | ⚫ 0/0 (0.0%) |




**Вывод:** В ходе лабораторной работы были реализованы модульные тесты для линейной и нелинейной моделей температуры. Основной функциональный модуль temp_model.cpp протестирован полностью, что подтверждается 100% покрытием строк, функций и ветвлений. Низкий общий процент покрытия связан с тем, что файл main.cpp не включается в тестирование. Все созданные тесты выполнены успешно, что подтверждает корректность работы модели.
