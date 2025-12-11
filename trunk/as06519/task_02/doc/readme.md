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
<p align="right">Группы АС-65</p>
<p align="right">Сунцова М. Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06519/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---
## Выполнение работы
---
### Тесты

```cpp
#include <gtest/gtest.h>
#include "../src/temp_model.h"
#include <cmath>

TEST(LinearModel, Basic) {
    LinParams p{0.75, 0.18};
    EXPECT_DOUBLE_EQ(linear_model(2.0, 1.0, p), 0.75*2.0 + 0.18*1.0);
}

TEST(LinearModel, ZeroInput) {
    LinParams p{0.5, 0.3};
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, p), 0.0);
}

TEST(LinearModel, NegativeInput) {
    LinParams p{0.5, 0.3};
    EXPECT_DOUBLE_EQ(linear_model(-2.0, -1.0, p), -1.0 - 0.3);
}

TEST(NonlinearModel, Basic) {
    NonlinParams p{0.75, 0.18, 0.07, 0.12};
    double expected = p.a*2 - p.b*1*1 + p.c*1 + p.d*sin(0);
    EXPECT_NEAR(nonlinear_model(2, 1, 1, 0, p), expected, 1e-9);
}

TEST(NonlinearModel, ZeroValues) {
    NonlinParams p{0.75, 0.18, 0.07, 0.12};
    EXPECT_DOUBLE_EQ(nonlinear_model(0, 0, 0, 0, p), 0.0);
}

TEST(NonlinearModel, Finite) {
    NonlinParams p{0.75, 0.18, 0.07, 0.12};
    double r = nonlinear_model(10, 5, 2, 1, p);
    EXPECT_TRUE(std::isfinite(r));
}
```

### Результат выполнения тестов:
```bash
1: [==========] Running 6 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 3 tests from LinearModel
1: [ RUN      ] LinearModel.Basic
1: [       OK ] LinearModel.Basic (0 ms)
1: [ RUN      ] LinearModel.ZeroInput
1: [       OK ] LinearModel.ZeroInput (0 ms)
1: [ RUN      ] LinearModel.NegativeInput
1: [       OK ] LinearModel.NegativeInput (0 ms)
1: [----------] 3 tests from LinearModel (0 ms total)
1: 
1: [----------] 3 tests from NonlinearModel
1: [ RUN      ] NonlinearModel.Basic
1: [       OK ] NonlinearModel.Basic (0 ms)
1: [ RUN      ] NonlinearModel.ZeroValues
1: [       OK ] NonlinearModel.ZeroValues (0 ms)
1: [ RUN      ] NonlinearModel.Finite
1: [       OK ] NonlinearModel.Finite (0 ms)
1: [----------] 3 tests from NonlinearModel (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 6 tests from 2 test suites ran. (0 ms total)
1: [  PASSED  ] 6 tests.
1/1 Test #1: AllTests .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
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
| **`temp_model.cpp`** | 🟢 4/4 (100.0%) | 🟢 2/2 (100.0%) | ⚫ 0/0 (0.0%) |




**Вывод:** В ходе лабораторной работы были реализованы модульные тесты для линейной и нелинейной моделей температуры. Основной функциональный модуль temp_model.cpp протестирован полностью, что подтверждается 100% покрытием строк, функций и ветвлений. Низкий общий процент покрытия связан с тем, что файл main.cpp не включается в тестирование. Все созданные тесты выполнены успешно, что подтверждает корректность работы модели.
