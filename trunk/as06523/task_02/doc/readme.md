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
<p align="right">Ярмак К. А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06523/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---

## Выполнение работы
---
### Тесты

```cpp
#include <gtest/gtest.h>
#include "../src/model.h"
#include <cmath>

TEST(LinearModelTest, BasicCalculation) {
    double result = linear_model(2.0, 1.0, 0.5, 0.3);
    EXPECT_DOUBLE_EQ(result, 0.5 * 2.0 + 0.3 * 1.0);
}

TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.15), 0.0);
}

TEST(LinearModelTest, NegativeInput) {
    double result = linear_model(-2.0, -1.0, 0.5, 0.3);
    EXPECT_DOUBLE_EQ(result, 0.5 * -2.0 + 0.3 * -1.0);
}


TEST(NonlinearModelTest, BasicCalculation) {
    double y_t = 2.0;
    double y_prev = 1.0;
    double u_t = 1.0;
    double u_prev = 0.0;
    Coeffs coeffs = {0.8, 0.2, 0.1, 0.05};
    double expected = coeffs.a * y_t - coeffs.b * y_prev * y_prev + coeffs.c * u_t + coeffs.d * sin(u_prev);
    EXPECT_NEAR(nonlinear_model(y_t, y_prev, u_t, u_prev, coeffs), expected, 1e-9);
}

TEST(NonlinearModelTest, ZeroValues) {
    Coeffs coeffs = {0.8, 0.2, 0.1, 0.05};
    EXPECT_DOUBLE_EQ(nonlinear_model(0, 0, 0, 0, coeffs), 0.0);
}

TEST(NonlinearModelTest, LargeValuesFinite) {
    Coeffs coeffs = {0.9, 0.1, 0.2, 0.3};
    double result = nonlinear_model(100, 50, 10, 5, coeffs);
    EXPECT_TRUE(std::isfinite(result));
}
```

Результат выполнения тестов:
```bash
Test project /home/kirill/VS_Code_Files/UNI/TMAU/TMAU-2025/trunk/as06523/task_02/src/build
    Start 1: LinearModelTest.BasicCalculation
1/6 Test #1: LinearModelTest.BasicCalculation .......   Passed    0.01 sec
    Start 2: LinearModelTest.ZeroInput
2/6 Test #2: LinearModelTest.ZeroInput ..............   Passed    0.00 sec
    Start 3: LinearModelTest.NegativeInput
3/6 Test #3: LinearModelTest.NegativeInput ..........   Passed    0.01 sec
    Start 4: NonlinearModelTest.BasicCalculation
4/6 Test #4: NonlinearModelTest.BasicCalculation ....   Passed    0.01 sec
    Start 5: NonlinearModelTest.ZeroValues
5/6 Test #5: NonlinearModelTest.ZeroValues ..........   Passed    0.00 sec
    Start 6: NonlinearModelTest.LargeValuesFinite
6/6 Test #6: NonlinearModelTest.LargeValuesFinite ...   Passed    0.01 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.04 sec
```

# GCC Code Coverage Report

## 📂 Overall coverage

| Metric        | Coverage |
|---------------|----------|
| **Lines**     | 🔴 4/22 (18.2%) |
| **Functions** | 🔴 2/3 (66.7%) |
| **Branches**  | 🔴 0/34 (0.0%) |

## 📄 File coverage

| File                   | Lines | Functions | Branches |
|------------------------|-------|-----------|----------|
| **`main.cpp`** | 🔴 0/18 (0.0%) | 🔴 0/1 (0.0%) | 🔴 0/34 (0.0%) |
| **`model.cpp`** | 🟢 4/4 (100.0%) | 🟢 2/2 (100.0%) | ⚫ 0/0 (0.0%) |

**Вывод:** В рамках лабораторной работы были успешно реализованы модульные тесты для линейной и нелинейной модели. Все 6 тестов прошли корректно, что подтверждает стабильность основных функций. Покрытие кода по строкам составило 18.2%, при этом 100% функций в model.cpp были протестированы.
