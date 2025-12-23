

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
<p align="right">Романюк Д.А.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
---
# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/). 
3. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
4. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
5. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
6. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.
## Выполнение работы

### Тесты
```cpp

#include <gtest/gtest.h>
#include "functions.h"
#include <cmath>

// ==================== ОСНОВНЫЕ ТЕСТЫ ЛИНЕЙНОЙ ФУНКЦИИ ====================

TEST(LinearModel, BasicCalculation) {
    EXPECT_DOUBLE_EQ(linear(10.0, 5.0), 0.92 * 10.0 + 0.08 * 5.0);
}

TEST(LinearModel, ZeroInputs) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0), 0.0);
}

TEST(LinearModel, OnlyState) {
    EXPECT_DOUBLE_EQ(linear(15.5, 0.0), a * 15.5);
}

TEST(LinearModel, OnlyInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 8.3), b * 8.3);
}

TEST(LinearModel, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear(-5.0, -3.0), a * (-5.0) + b * (-3.0));
}

TEST(LinearModel, FractionalValues) {
    double result = linear(2.75, 4.125);
    double expected = 0.92 * 2.75 + 0.08 * 4.125;
    EXPECT_NEAR(result, expected, 1e-12);
}

// ==================== ОСНОВНЫЕ ТЕСТЫ НЕЛИНЕЙНОЙ ФУНКЦИИ ====================

TEST(NonlinearModel, BasicCalculation) {
    double result = nonlinear(12.0, 8.0, 6.0, 4.0);
    double expected = a * 12.0 - b * 8.0 * 8.0 + c * 6.0 + d * sin(4.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModel, AllZeros) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModel, OnlyCurrentState) {
    EXPECT_DOUBLE_EQ(nonlinear(9.5, 0.0, 0.0, 0.0), a * 9.5);
}

TEST(NonlinearModel, OnlyPreviousState) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 7.2, 0.0, 0.0), -b * 7.2 * 7.2);
}

TEST(NonlinearModel, OnlyInputs) {
    double result = nonlinear(0.0, 0.0, 3.0, 1.57);
    double expected = c * 3.0 + d * sin(1.57);
    EXPECT_NEAR(result, expected, 1e-12);
}

TEST(NonlinearModel, NegativeInputs) {
    double result = nonlinear(4.0, 2.0, -3.0, -1.0);
    double expected = a * 4.0 - b * 2.0 * 2.0 + c * (-3.0) + d * sin(-1.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModel, HighPrecision) {
    double yt = 1.234567, yt1 = 9.876543, ut = 2.718281, ut1 = 3.141592;
    double result = nonlinear(yt, yt1, ut, ut1);
    double expected = a * yt - b * yt1 * yt1 + c * ut + d * sin(ut1);
    EXPECT_NEAR(result, expected, 1e-10);
}

// ==================== СПЕЦИАЛЬНЫЕ ТЕСТЫ ====================

TEST(SystemParameters, ValidRanges) {
    EXPECT_GT(a, 0.0);
    EXPECT_LT(a, 1.0);
    EXPECT_GT(b, 0.0);
    EXPECT_GT(c, 0.0);
    EXPECT_GT(d, 0.0);
}

TEST(ModelsComparison, DifferentResults) {
    double yt = 10.0, ut = 5.0;
    double linear_result = linear(yt, ut);
    double nonlinear_result = nonlinear(yt, yt, ut, ut);
    EXPECT_NE(linear_result, nonlinear_result);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 ```
 [==========] Running 15 tests from 4 test suites.
[----------] Global test environment set-up.
[----------] 6 tests from LinearModel
[ RUN      ] LinearModel.BasicCalculation
[       OK ] LinearModel.BasicCalculation (0 ms)
[ RUN      ] LinearModel.ZeroInputs
[       OK ] LinearModel.ZeroInputs (0 ms)
[ RUN      ] LinearModel.OnlyState
[       OK ] LinearModel.OnlyState (0 ms)
[ RUN      ] LinearModel.OnlyInput
[       OK ] LinearModel.OnlyInput (0 ms)
[ RUN      ] LinearModel.NegativeValues
[       OK ] LinearModel.NegativeValues (0 ms)
[ RUN      ] LinearModel.FractionalValues
[       OK ] LinearModel.FractionalValues (0 ms)
[----------] 6 tests from LinearModel (6 ms total)

[----------] 7 tests from NonlinearModel
[ RUN      ] NonlinearModel.BasicCalculation
[       OK ] NonlinearModel.BasicCalculation (0 ms)
[ RUN      ] NonlinearModel.AllZeros
[       OK ] NonlinearModel.AllZeros (0 ms)
[ RUN      ] NonlinearModel.OnlyCurrentState
[       OK ] NonlinearModel.OnlyCurrentState (0 ms)
[ RUN      ] NonlinearModel.OnlyPreviousState
[       OK ] NonlinearModel.OnlyPreviousState (0 ms)
[ RUN      ] NonlinearModel.OnlyInputs
[       OK ] NonlinearModel.OnlyInputs (0 ms)
[ RUN      ] NonlinearModel.NegativeInputs
[       OK ] NonlinearModel.NegativeInputs (0 ms)
[ RUN      ] NonlinearModel.HighPrecision
[       OK ] NonlinearModel.HighPrecision (0 ms)
[----------] 7 tests from NonlinearModel (9 ms total)

[----------] 1 test from SystemParameters
[ RUN      ] SystemParameters.ValidRanges
[       OK ] SystemParameters.ValidRanges (0 ms)
[----------] 1 test from SystemParameters (0 ms total)

[----------] 1 test from ModelsComparison
[ RUN      ] ModelsComparison.DifferentResults
[       OK ] ModelsComparison.DifferentResults (0 ms)
[----------] 1 test from ModelsComparison (0 ms total)

[----------] Global test environment tear-down
[==========] 15 tests from 4 test suites ran. (33 ms total)
[  PASSED  ] 15 tests.
### Покрытие кода тестами
─────────────────────────────────────────
File                  Lines    Coverage
─────────────────────────────────────────
src/functions.cpp         8      100.0%
src/main.cpp             45       77.8%
─────────────────────────────────────────
TOTAL                    53       81.1%
─────────────────────────────────────────
**Вывод:** Успешно разработана система модульного тестирования с 15 тестами, обеспечивающая 81% покрытие кода и полную проверку математических функций программы.