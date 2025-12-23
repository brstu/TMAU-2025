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
<p align="right">Касьяник К. А.</p>
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
## Выполнение работы
---
### Тесты

```cpp
#include <gtest/gtest.h>
#include "../src/model.h"
#include <cmath>


TEST(LinearStepTest, ZeroInputGivesZeroOutput) {
    LinearParams p{0.86, 0.23};
    EXPECT_DOUBLE_EQ(linear_step(0.0, 0.0, p), 0.0);
}

TEST(LinearStepTest, WorksWithPositiveValues) {
    LinearParams p{0.5, 0.25};
    EXPECT_DOUBLE_EQ(linear_step(2.0, 4.0, p), 0.5 * 2.0 + 0.25 * 4.0);
}

TEST(LinearStepTest, WorksWithNegativeValues) {
    LinearParams p{0.8, 0.2};
    EXPECT_DOUBLE_EQ(linear_step(-3.0, -2.0, p), 0.8 * -3.0 + 0.2 * -2.0);
}


TEST(NonlinearStepTest, NonlinearIncludesSinCorrectly) {
    NonlinearParams p{0.69, 0.15, 0.10, 0.21};
    double y1 = 1.0, y2 = 1.0, u1 = 1.0, u2 = 0.0;

    double expected = p.a * y1 - p.bnl * (y2 * y2) + p.c * u1 + p.d * std::sin(u2);

    EXPECT_NEAR(nonlinear_step(y1, y2, u1, u2, p), expected, 1e-9);
}

TEST(NonlinearStepTest, HandlesNegativeAndPositiveMix) {
    NonlinearParams p{0.7, 0.2, 0.1, 0.05};

    double result = nonlinear_step(-2.0, 1.0, 3.0, -1.0, p);

    double expected = 0.7 * -2.0 - 0.2 * (1.0 * 1.0) + 0.1 * 3.0 + 0.05 * std::sin(-1.0);

    EXPECT_NEAR(result, expected, 1e-9);
}
```

### Результат выполнения тестов:
```bash
1: [==========] Running 5 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 3 tests from LinearStepTest
1: [ RUN      ] LinearStepTest.ZeroInputGivesZeroOutput
1: [       OK ] LinearStepTest.ZeroInputGivesZeroOutput (0 ms)
1: [ RUN      ] LinearStepTest.WorksWithPositiveValues
1: [       OK ] LinearStepTest.WorksWithPositiveValues (0 ms)
1: [ RUN      ] LinearStepTest.WorksWithNegativeValues
1: [       OK ] LinearStepTest.WorksWithNegativeValues (0 ms)
1: [----------] 3 tests from LinearStepTest (0 ms total)
1: 
1: [----------] 2 tests from NonlinearStepTest
1: [ RUN      ] NonlinearStepTest.NonlinearIncludesSinCorrectly
1: [       OK ] NonlinearStepTest.NonlinearIncludesSinCorrectly (0 ms)
1: [ RUN      ] NonlinearStepTest.HandlesNegativeAndPositiveMix
1: [       OK ] NonlinearStepTest.HandlesNegativeAndPositiveMix (0 ms)
1: [----------] 2 tests from NonlinearStepTest (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 5 tests from 2 test suites ran. (0 ms total)
1: [  PASSED  ] 5 tests.
1/1 Test #1: ModelUnitTests ...................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```


# Процент покрытия кода тестами
```
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
model.cpp                                      4       4   100%
------------------------------------------------------------------------------
TOTAL                                          4       4   100%
------------------------------------------------------------------------------
```



**Вывод:** В ходе выполнения лабораторной работы были разработаны и запущены модульные тесты для линейной и нелинейной температурной модели. Файл model.cpp прошёл полное тестирование, что подтверждается стопроцентным покрытием строк, функций и ветвлений. Все созданные тесты завершились успешно, тем самым подтверждая корректность функционирования реализованной модели.
