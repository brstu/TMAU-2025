<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Занько Я.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.
---


## Ход работы
---

### Тесты
```cpp
#include <gtest/gtest.h>
#include "model.h"
#include <vector>
#include <cmath>

TEST(LinearModelTest, ZeroInput) {
    ModelParams params{10, 0.9, 0.02, 0.0, 0.0};
    std::vector<double> u(params.N + 1, 0.0);

    std::vector<double> y = linear_model(params, u, 0.0);

    for (double v : y) {
        EXPECT_NEAR(v, 0.0, 1e-9);
    }
}

TEST(LinearModelTest, Convergence) {
    ModelParams params{50, 0.9, 0.02, 0.0, 0.0};
    std::vector<double> u(params.N + 1, 1.0);

    std::vector<double> y = linear_model(params, u, 0.0);

    EXPECT_NEAR(y.back(), 0.2, 1e-2);
}

TEST(NonlinearModelTest, FiniteValues) {
    ModelParams params{30, 0.9, 0.02, 0.03, 0.1};
    std::vector<double> u(params.N + 1, 1.0);

    std::vector<double> y = nonlinear_model(params, u, 0.0, 0.0);

    for (double v : y) {
        EXPECT_TRUE(std::isfinite(v));
    }
}
```

### Результат выполнения тестов:
```bash
1: [==========] Running 3 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 2 tests from LinearModelTest
1: [ RUN      ] LinearModelTest.ZeroInput
1: [       OK ] LinearModelTest.ZeroInput (0 ms)
1: [ RUN      ] LinearModelTest.Convergence
1: [       OK ] LinearModelTest.Convergence (0 ms)
1: [----------] 2 tests from LinearModelTest (0 ms total)
1: 
1: [----------] 1 test from NonlinearModelTest
1: [ RUN      ] NonlinearModelTest.FiniteValues
1: [       OK ] NonlinearModelTest.FiniteValues (0 ms)
1: [----------] 1 test from NonlinearModelTest (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 3 tests from 2 test suites ran. (0 ms total)
1: [  PASSED  ] 3 tests.
1/1 Test #1: model_tests ......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```


# GCC Code Coverage Report
```bash
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
model.cpp                                     13      13   100%
------------------------------------------------------------------------------
TOTAL                                         13      13   100%
------------------------------------------------------------------------------
```




__Вывод:__ в ходе лабораторной работы были разработаны и успешно выполнены модульные тесты с использованием фреймворка Google Test для основных функций программы. Все тесты завершились без ошибок, что подтверждает корректность реализованных моделей. Анализ покрытия кода показал 100% покрытие файла model.cpp, что свидетельствует о полном тестировании реализованной логики и достаточном качестве тестов.
