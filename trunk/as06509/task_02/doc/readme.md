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
<p align="right">Колбашко А. В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06509/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---

## Выполнение работы
---
### Тесты

```cpp
#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

TEST(LinearModelTest, BaseValues) {
    Constants con;
    std::vector<double> u(10, 4.0);
    auto y = linear(con, u);

    EXPECT_EQ(y.size(), con.n + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
}

TEST(LinearModelTest, ZeroInput) {
    Constants con;
    std::vector<double> u(10, 0.0);
    auto y = linear(con, u);

    EXPECT_NEAR(y[1], 25.0 * con.a, 1e-6);
    EXPECT_NEAR(y[2], 25.0 * con.a * con.a, 1e-6);
}

TEST(LinearModelTest, InsufficientInput) {
    Constants con;
    std::vector<double> u(con.n - 1, 1.0); 
    EXPECT_THROW(linear(con, u), std::invalid_argument);
}


TEST(NonlinearModelTest, StartValues) {
    Constants con;
    std::vector<double> u(10, 4.0);
    auto y = nonlinear(con, u);

    EXPECT_EQ(y.size(), con.n + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
    EXPECT_DOUBLE_EQ(y[1], 25.0);
}

TEST(NonlinearModelTest, InputInfluence) {
    Constants con;
    std::vector<double> u1(10, 4.0);
    std::vector<double> u2(10, 8.0);

    auto y1 = nonlinear(con, u1);
    auto y2 = nonlinear(con, u2);

    EXPECT_GT(y2.back(), y1.back());
}

TEST(NonlinearModelTest, OutputChanges) {
    Constants con;
    std::vector<double> u = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto y = nonlinear(con, u);

    bool all_equal = true;
    for (int i = 1; i < static_cast<int>(y.size()); ++i) {
        if (std::fabs(y[i] - y[0]) > 1e-9) {
            all_equal = false;
            break;
        }
    }
    EXPECT_FALSE(all_equal);
}

TEST(NonlinearModelTest, InsufficientInput) {
    Constants con;
    std::vector<double> u(con.n - 2, 1.0); 
    EXPECT_THROW(nonlinear(con, u), std::invalid_argument);
}
```
Результат выполнения тестов:
```bash
[==========] Running 7 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from LinearModelTest
[ RUN      ] LinearModelTest.BaseValues
[       OK ] LinearModelTest.BaseValues (0 ms)
[ RUN      ] LinearModelTest.ZeroInput
[       OK ] LinearModelTest.ZeroInput (0 ms)
[ RUN      ] LinearModelTest.InsufficientInput
[       OK ] LinearModelTest.InsufficientInput (0 ms)
[----------] 3 tests from LinearModelTest (1 ms total)

[----------] 4 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.StartValues
[       OK ] NonlinearModelTest.StartValues (0 ms)
[ RUN      ] NonlinearModelTest.InputInfluence
[       OK ] NonlinearModelTest.InputInfluence (0 ms)
[ RUN      ] NonlinearModelTest.OutputChanges
[       OK ] NonlinearModelTest.OutputChanges (0 ms)
[ RUN      ] NonlinearModelTest.InsufficientInput
[       OK ] NonlinearModelTest.InsufficientInput (0 ms)
[----------] 4 tests from NonlinearModelTest (0 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 2 test suites ran. (2 ms total)
[  PASSED  ] 7 tests.
```

# gcovr отчёт
-------------------------------------------------------------------------------
File                  Lines     Exec  Cover   Functions  Exec  Cover
-------------------------------------------------------------------------------
src/model.cpp           28        26    93%       2       2  100%
-------------------------------------------------------------------------------
TOTAL                   28        26    93%       2       2  100%
-------------------------------------------------------------------------------

**Вывод:** В рамках лабораторной работы были успешно реализованы модульные тесты Google Tests для линейной и нелинейной модели САУ. Все 7 тестов успешно прошли, что подтверждает корректность основных функций. Покрытие кода по строкам составило 93%, при этом 100% функций в model.cpp были протестированы.