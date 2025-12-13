<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Ануфриенко М.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>


# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.


## Выполнение работы
---
#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

TEST(LinearModelTest, ZeroInputs) {
    EXPECT_DOUBLE_EQ(linearModel(0.0, 0.0, 0.8, 0.15), 0.0);
}

TEST(LinearModelTest, BasicCase) {
    double r = linearModel(1.0, 1.0, 0.8, 0.15);
    EXPECT_NEAR(r, 0.95, 1e-12);
}

TEST(LinearModelTest, NegativeValues) {
    double r = linearModel(-2.0, -3.0, 0.8, 0.15);
    EXPECT_NEAR(r, -1.6 - 0.45, 1e-12);
}


// ========= НЕЛИНЕЙНАЯ МОДЕЛЬ =========

TEST(NonlinearModelTest, ZeroInputs) {
    double r = nonlinearModel(0.0, 0.0, 0.0, 0.0,
                              0.8, 0.15, 0.05);
    EXPECT_DOUBLE_EQ(r, 0.0);
}

TEST(NonlinearModelTest, BasicCase) {
    double r = nonlinearModel(0.8, 0.15, 0.15, 1.0,
                              1.0, 1.0, 1.0);
    double expected = 0.8 * 1.0 - 0.15 * 1.0 * 1.0 + 0.15 * 1.0 + 1.0 * sin(1.0);
    EXPECT_NEAR(r, expected, 1e-12);
}

TEST(NonlinearModelTest, NonlinearEffect) {
    double r1 = nonlinearModel(1.0, 1.0, 0.0, 0.0, 0.8, 0.15, 1.0);
    double r2 = nonlinearModel(1.0, 2.0, 0.0, 0.0, 0.8, 0.15, 1.0);
    EXPECT_LT(r2, r1);
}

TEST(NonlinearModelTest, SinTermAffectsOutput) {
    double r = nonlinearModel(1.0, 0.0, 0.0, 0.05,
                              0.0, 0.0, M_PI/2); // sin = 1
    EXPECT_NEAR(r, 0.05, 1e-12);
}
### Тесты
---
[==========] Running 7 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from LinearModelTest
[ RUN      ] LinearModelTest.ZeroInputs
[       OK ] LinearModelTest.ZeroInputs (0 ms)
[ RUN      ] LinearModelTest.BasicCase
[       OK ] LinearModelTest.BasicCase (0 ms)
[ RUN      ] LinearModelTest.NegativeValues
[       OK ] LinearModelTest.NegativeValues (0 ms)
[----------] 3 tests from LinearModelTest (0 ms total)

[----------] 4 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.ZeroInputs
[       OK ] NonlinearModelTest.ZeroInputs (0 ms)
[ RUN      ] NonlinearModelTest.BasicCase
[       OK ] NonlinearModelTest.BasicCase (0 ms)
[ RUN      ] NonlinearModelTest.NonlinearEffect
[       OK ] NonlinearModelTest.NonlinearEffect (0 ms)
[ RUN      ] NonlinearModelTest.SinTermAffectsOutput
[       OK ] NonlinearModelTest.SinTermAffectsOutput (0 ms)
[----------] 4 tests from NonlinearModelTest (0 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 7 tests.

```cpp