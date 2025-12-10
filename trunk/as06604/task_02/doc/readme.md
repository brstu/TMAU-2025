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
<p align="right">Гончерёнок К. А.</p>
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

## Выполнение работы

---

### Тесты

```cpp
#include <gtest/gtest.h>
#include "../src/t_model.h"
#include <cmath>

// lin
TEST(LinearModel, ZeroInputZeroState) {
    ParamsLin p{0.77, 0.29};
    EXPECT_DOUBLE_EQ(model_linear(0.0, 0.0, p), 0.0);
}

TEST(LinearModel, BasicCalculation) {
    ParamsLin p{0.77, 0.29};
    double expected = 0.77 * 10.0 + 0.29 * 2.0;
    EXPECT_DOUBLE_EQ(model_linear(10.0, 2.0, p), expected);
}

TEST(LinearModel, NegativeValues) {
    ParamsLin p{0.5, 0.5};
    double expected = 0.5 * (-4.0) + 0.5 * (-6.0);
    EXPECT_DOUBLE_EQ(model_linear(-4.0, -6.0, p), expected);
}


// nonlin
TEST(NonlinearModel, ZeroAll) {
    ParamsNonlin p{0.86, 0.15, 0.10, 0.11};
    EXPECT_DOUBLE_EQ(model_nonlinear(0, 0, 0, 0, p), 0.0);
}

TEST(NonlinearModel, NoSinEffect) {
    ParamsNonlin p{0.86, 0.15, 0.10, 0.11};
    double y1 = 5.0, y2 = 1.0, u1 = 2.0, u2 = 0.0;
    double expected = 0.86 * y1 - 0.15 * (y2 * y2) + 0.10 * u1 + 0.11 * std::sin(0.0);
    EXPECT_NEAR(model_nonlinear(y1, y2, u1, u2, p), expected, 1e-9);
}

TEST(NonlinearModel, WithSinus) {
    ParamsNonlin p{0.86, 0.15, 0.10, 0.11};
    double u2 = M_PI / 2;
    double expected = 0.86 * 3.0 - 0.15 * (2.0 * 2.0) + 0.10 * 1.0 + 0.11 * std::sin(u2);

    EXPECT_NEAR(model_nonlinear(3.0, 2.0, 1.0, u2, p), expected, 1e-9);
}
```

### Результат выполнения тестов:
```bash
1: [==========] Running 6 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 3 tests from LinearModel
1: [ RUN      ] LinearModel.ZeroInputZeroState
1: [       OK ] LinearModel.ZeroInputZeroState (0 ms)
1: [ RUN      ] LinearModel.BasicCalculation
1: [       OK ] LinearModel.BasicCalculation (0 ms)
1: [ RUN      ] LinearModel.NegativeValues
1: [       OK ] LinearModel.NegativeValues (0 ms)
1: [----------] 3 tests from LinearModel (0 ms total)
1: 
1: [----------] 3 tests from NonlinearModel
1: [ RUN      ] NonlinearModel.ZeroAll
1: [       OK ] NonlinearModel.ZeroAll (0 ms)
1: [ RUN      ] NonlinearModel.NoSinEffect
1: [       OK ] NonlinearModel.NoSinEffect (0 ms)
1: [ RUN      ] NonlinearModel.WithSinus
1: [       OK ] NonlinearModel.WithSinus (0 ms)
1: [----------] 3 tests from NonlinearModel (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 6 tests from 2 test suites ran. (0 ms total)
1: [  PASSED  ] 6 tests.
1/1 Test #1: test_model .......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```


# GCC Code Coverage Report

## 📂 Overall coverage

| Metric        | Coverage |
|---------------|----------|
| **Lines**     | 🔴 7/28 (25.0%) |
| **Functions** | 🔴 2/4 (50.0%) |
| **Branches**  | 🔴 0/36 (0.0%) |

## 📄 File coverage

| File                   | Lines | Functions | Branches |
|------------------------|-------|-----------|----------|
| **`main.cpp`** | 🔴 0/21 (0.0%) | 🔴 0/2 (0.0%) | 🔴 0/36 (0.0%) |
| **`t_model.cpp`** | 🟢 7/7 (100.0%) | 🟢 2/2 (100.0%) | ⚫ 0/0 (0.0%) |


**Вывод:** в лабораторной работе реализованы модульные тесты для линейной и нелинейной моделей температуры. Файл t_model.cpp покрыт тестами на 100%. Все тесты прошли успешно, что подтверждает корректность модели.
