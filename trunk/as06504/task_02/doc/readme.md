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
<p align="right">Дацкевич М. Г.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
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
#include "../src/model.h"

TEST(LinearModelTest, ZeroInput) {
    LinearCfg cfg{0.5, 0.3};
    EXPECT_DOUBLE_EQ(linearStep(0.0, 0.0, cfg), 0.0);
}

TEST(LinearModelTest, PositiveInput) {
    LinearCfg cfg{0.5, 0.3};
    EXPECT_NEAR(linearStep(2.0, 1.0, cfg), 1.3, 1e-6);
}

TEST(NonlinearModelTest, ZeroInput) {
    NonlinearCfg cfg{0.5, 0.2, 0.1, 0.05};
    EXPECT_DOUBLE_EQ(nonlinearStep(0.0, 0.0, 0.0, 0.0, cfg), 0.0);
}

TEST(NonlinearModelTest, MixedInput) {
    NonlinearCfg cfg{0.5, 0.2, 0.1, 0.05};
    double result = nonlinearStep(1.0, 2.0, 1.0, 0.5, cfg);
    double expected = 0.5 * 1.0 - 0.2 * 4.0 + 0.1 * 1.0 + 0.05 * std::sin(0.5);
    EXPECT_NEAR(result, expected, 1e-6);
}
```

### Результат тестов:
```bash
1: [==========] Running 4 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 2 tests from LinearModelTest
1: [ RUN      ] LinearModelTest.ZeroInput
1: [       OK ] LinearModelTest.ZeroInput (0 ms)
1: [ RUN      ] LinearModelTest.PositiveInput
1: [       OK ] LinearModelTest.PositiveInput (0 ms)
1: [----------] 2 tests from LinearModelTest (0 ms total)
1: 
1: [----------] 2 tests from NonlinearModelTest
1: [ RUN      ] NonlinearModelTest.ZeroInput
1: [       OK ] NonlinearModelTest.ZeroInput (0 ms)
1: [ RUN      ] NonlinearModelTest.MixedInput
1: [       OK ] NonlinearModelTest.MixedInput (0 ms)
1: [----------] 2 tests from NonlinearModelTest (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 4 tests from 2 test suites ran. (0 ms total)
1: [  PASSED  ] 4 tests.
1/1 Test #1: RunTests .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

### Покрытие кода тестами
```bash
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

**Вывод:** В работе выполнены модульные тесты для линейной и нелинейной моделей, `model.cpp` покрыт на 100%, все тесты пройдены успешно.
