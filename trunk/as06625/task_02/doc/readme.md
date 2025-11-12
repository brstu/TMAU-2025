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
<p align="right">Ярома А.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06625/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---

## Выполнение работы
---
### Тесты
```
#include <gtest/gtest.h>
#include <cmath>
#include "model.h"

TEST(LinearModelTest, BaseValues) {
    Params prm;
    std::vector<double> input(10, 4.0);
    auto y = lin_model(prm, input);

    EXPECT_EQ(y.size(), prm.steps + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
}

TEST(LinearModelTest, ZeroInput) {
    Params prm;
    std::vector<double> input(10, 0.0);
    auto y = lin_model(prm, input);

    EXPECT_NEAR(y[1], 25.0 * prm.alpha, 1e-6);
    EXPECT_NEAR(y[2], 25.0 * prm.alpha * prm.alpha, 1e-6);
}

TEST(LinearModelTest, InsufficientInput) {
    Params prm;
    std::vector<double> input(prm.steps - 1, 1.0);
    EXPECT_THROW(lin_model(prm, input), std::invalid_argument);
}


TEST(NonlinearModelTest, StartValues) {
    Params prm;
    std::vector<double> input(10, 4.0);
    auto y = nonlin_model(prm, input);

    EXPECT_EQ(y.size(), prm.steps + 1);
    EXPECT_DOUBLE_EQ(y[0], 25.0);
    EXPECT_DOUBLE_EQ(y[1], 25.0);
}

TEST(NonlinearModelTest, InputInfluence) {
    Params prm;
    std::vector<double> u1(10, 4.0);
    std::vector<double> u2(10, 8.0);

    auto y1 = nonlin_model(prm, u1);
    auto y2 = nonlin_model(prm, u2);

    EXPECT_GT(y2.back(), y1.back());
}

TEST(NonlinearModelTest, OutputChanges) {
    Params prm;
    std::vector<double> input = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto y = nonlin_model(prm, input);

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
    Params prm;
    std::vector<double> input(prm.steps - 2, 1.0);
    EXPECT_THROW(nonlin_model(prm, input), std::invalid_argument);
}
```
Результат выполнения тестов:
```

6: [==========] Running 1 test from 1 test suite.
6: [----------] Global test environment set-up.
6: [----------] 1 test from NonlinearModelTest
6: [ RUN      ] NonlinearModelTest.OutputChanges
6: [       OK ] NonlinearModelTest.OutputChanges (0 ms)
6: [----------] 1 test from NonlinearModelTest (0 ms total)
6: 
6: [----------] Global test environment tear-down
6: [==========] 1 test from 1 test suite ran. (0 ms total)
6: [  PASSED  ] 1 test.

7: Test command: D:\progr\TMAU-2025\trunk\as06625\task_02\src\cmake-build-debug\runTests.exe "--gtest_filter=NonlinearModelTest.InsufficientInput" "--gtest_also_run_disabled_tests"
7: Working Directory: D:/progr/TMAU-2025/trunk/as06625/task_02/src/cmake-build-debug
7: Test timeout computed to be: 9999879
7: Running main() from D:/progr/TMAU-2025/trunk/as06625/task_02/src/cmake-build-debug/_deps/googletest-src/googletest/src/gtest_main.cc
7: Note: Google Test filter = NonlinearModelTest.InsufficientInput
7: [==========] Running 1 test from 1 test suite.
7: [----------] Global test environment set-up.
7: [----------] 1 test from NonlinearModelTest
7: [ RUN      ] NonlinearModelTest.InsufficientInput
7: [       OK ] NonlinearModelTest.InsufficientInput (0 ms)
7: [----------] 1 test from NonlinearModelTest (0 ms total)
7: 
7: [----------] Global test environment tear-down
7: [==========] 1 test from 1 test suite ran. (0 ms total)
7: [  PASSED  ] 1 test.

100% tests passed, 0 tests failed out of 7

Total Test time (real) =   0.07 sec
```

# gcovr отчёт
-------------------------------------------------------------------------------
File                  Lines     Exec  Cover   Functions  Exec  Cover
-------------------------------------------------------------------------------
src/model.cpp           34        31    91%       2       2  100%
-------------------------------------------------------------------------------
TOTAL                   34        31    91%       2       2  100%
-------------------------------------------------------------------------------

**Вывод:** В рамках лабораторной работы были успешно реализованы модульные тесты Google Tests для линейной и нелинейной модели САУ. Все 7 тестов успешно прошли, что подтверждает корректность основных функций. Покрытие кода по строкам составило 91%, при этом 100% функций в model.cpp были протестированы.